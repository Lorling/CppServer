#include "EventLoop.h"
#include <vector>

EventLoop::EventLoop() : ep(nullptr), quit(false){
    ep = new Epoll();
}

EventLoop::~EventLoop(){
    delete ep;
}

void EventLoop::loop(){
    while(!quit){
        std::vector<Channel *> channels = ep->poll();
        for(auto i : channels){
            i->handleEvent();
        }
    }
}

void EventLoop::updateChannel(Channel * ch){
    ep->updateChannel(ch);
}
