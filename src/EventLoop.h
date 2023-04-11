#ifndef __EVENTLOOP__
#define __EVENTLOOP__

#include <functional>

class Epoll;
class Channel;
class ThreadPool;
class EventLoop{
private:
    Epoll *ep;
    ThreadPool * pool;
public:
    EventLoop();
    ~EventLoop();

    void loop();
    void updateChannel(Channel *);
    void submitThread(std::function<void()>);
};

#endif
