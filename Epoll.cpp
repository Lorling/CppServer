#include "Epoll.h"
#include "util.h"
#include "Channel.h"
#include <cstring>
#include <unistd.h>

Epoll::Epoll() : epfd(-1), events(nullptr){
    epfd = epoll_create1(0);
    errif(epfd == -1, "epoll create");
    events = new epoll_event[1024];
    memset(events, 0, sizeof events * 1024);
}

Epoll::~Epoll(){
    if(epfd != -1){
        close(epfd);
        epfd = -1;
    }
    delete [] events;
}

void Epoll::addFd(int fd, uint32_t op){
    struct epoll_event ev;
    memset(&ev, 0, sizeof ev);
    ev.data.fd = fd;
    ev.events = op;
    errif(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1, "epoll add");
}

std::vector<Channel *> Epoll::poll(int timeout){
    std::vector<Channel *> activeChannels;
    int nfds = epoll_wait(epfd, events, 1024, timeout);
    errif(nfds == -1, "epoll wait");
    for(int i = 0; i < nfds; i++){
        Channel * ch = (Channel*)events[i].data.ptr;
        ch->setRevents(events[i].events);
        activeChannels.push_back(ch);
    }
    return activeChannels;
}

void Epoll::updateChannel(Channel * channel){
    int fd = channel->getFd();
    struct epoll_event ev;
    memset(&ev,0,sizeof ev);
    ev.data.ptr = channel;
    ev.events = channel->getEvents();
    if(channel->getInEpoll()){
        errif(epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev), "epoll mod");
    }
    else {
        errif(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev), "epoll add");
        channel->setInEpoll();
    }
}
