#ifndef __EVENTLOOP__
#define __EVENTLOOP__

#include "Channel.h"
#include "Epoll.h"

class EventLoop{
private:
    Epoll *ep;
    bool quit;
public:
    EventLoop();
    ~EventLoop();

    void loop();
    void updateChannel(Channel *);
};

#endif
