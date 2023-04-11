#include "Channel.h"
#include "EventLoop.h"

Channel::Channel(EventLoop *_loop,int _fd) : loop(_loop), fd(_fd), events(0), revents(0), inEpoll(false),useThread(true){
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
        //if(useThread) loop->submitThread(readCallback);
        //else 
        readCallback();
    if(revents & (EPOLLOUT))
        //if(useThread) loop->submitThread(writeCallback);
        //else 
        writeCallback();
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

void Channel::setUseThread(bool flag){
    useThread = flag;
}
