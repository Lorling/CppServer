#ifndef  __EPOLL__
#define  __EPOLL__

#include <sys/epoll.h>
#include <vector>
#include <unistd.h>
#include <cstring>
#include "Channel.h"
#include "util.h"

class Epoll{
private:
    int epfd;
    struct epoll_event *events;
public:
    Epoll() : epfd(-1), events(nullptr){
        epfd = epoll_create1(0);
        errif(epfd == -1, "epoll create");
        events = new epoll_event[1024];
        memset(events, 0, sizeof events);
    }
        
    ~Epoll(){
        if(epfd != -1){
            close(epfd);
            epfd = -1;
        }
        delete [] events;
    }

    std::vector<Channel *> pool(int timeout = -1){
        std::vector<Channel *> res;
        int nfds = epoll_wait(epfd, events, 1024, timeout);
        errif(nfds == -1, "epoll wait");
        for(int i = 0; i < nfds; i++){
            Channel * ch = (Channel *)events[i].data.ptr;
            ch->setRevents(events[i].events);
            res.push_back(ch);
        }
        return res;
    }
    void updateChannel(Channel * channel){//jiang Channel jia ru dao epoll huozhe gengxin zhuangtai
        int fd = channel->getFd();
        struct epoll_event ev;
        memset(&ev, 0, sizeof ev);
        ev.data.ptr = channel;
        ev.events = channel->getEvents();
        if(channel->getInEpoll()){
            errif(epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev) == -1, "epoll mod");
        }
        else {
            errif(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1, "epoll add");
            channel->setInEpoll();
        }
    }
    void deleteChannel(Channel * channel){
        int fd = channel->getFd();
        errif(epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL) == -1, "epoll delete");
        channel->setInEpoll(false);
    }
};

#endif
