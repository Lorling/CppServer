#include "EventLoop.h"
#include "Epoll.h"
#include "ThreadPool.h"
#include "Channel.h"
#include <vector>

EventLoop::EventLoop() : ep(nullptr){
    ep = new Epoll();
}

EventLoop::~EventLoop(){
    delete ep;
}

void EventLoop::loop(){
    while(true){
        std::vector<Channel *> chs = ep->pool();
        for(auto i : chs)
            i->handleEvent();
    }
}

void EventLoop::updateChannel(Channel * ch){
    ep->updateChannel(ch);
}
