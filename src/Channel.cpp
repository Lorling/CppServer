#include "Channel.h"
#include "EventLoop.h"
#include <sys/epoll.h>
#include <unistd.h>

Channel::Channel(EventLoop *_loop,int _fd) : loop(_loop), fd(_fd), events(0), revents(0), inEpoll(false){
}

Channel::~Channel(){
    if(fd != -1){
        close(fd);
        fd = -1; 
    }
}   

void Channel::enableReading(){
    events |= EPOLLIN | EPOLLPRI;
    loop->updateChannel(this);
}
   
void Channel::handleEvent(){
    if(revents & (EPOLLIN | EPOLLPRI))
        readCallback();
    if(revents & (EPOLLOUT))
        sendCallback();
}   

int Channel::getFd(){
    return fd;
}

uint32_t Channel::getEvents(){
    return events;
}

uint32_t Channel::getRevents(){
    return revents;
}

bool Channel::getInEpoll(){
    return inEpoll;
}

void Channel::setInEpoll(bool condition){
    inEpoll = condition;
}

void Channel::useET(){
    events |= EPOLLET;
    loop->updateChannel(this);
}
   
void Channel::setRevents(uint32_t _ev){
    revents = _ev;
}

void Channel::setReadCallback(std::function<void()> _cb){
    readCallback = _cb;
}

void Channel::setSendCallback(std::function<void()> _cb){
    sendCallback = _cb;
}
