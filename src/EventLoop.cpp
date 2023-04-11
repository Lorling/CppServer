#include "EventLoop.h"
#include "Epoll.h"
#include "ThreadPool.h"
#include "Channel.h"
#include <vector>

EventLoop::EventLoop() : ep(nullptr), pool(nullptr){
    ep = new Epoll();
    pool = new ThreadPool(1);
}

EventLoop::~EventLoop(){
    delete pool;
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

void EventLoop::submitThread(std::function<void()> func){
    pool->submit(func);
}
