#ifndef __CHANNEL__
#define __CHANNEL__

#include <sys/epoll.h>
#include <functional>
#include <unistd.h>
#include "EventLoop.h"

class EventLoop;
class Channel{
private:
    EventLoop * loop;
    int fd;
    uint32_t events;//xi wang jian ting de shi jian
    uint32_t revents;//zheng zai yun xing
    bool inEpoll;
    bool useThread;
    std::function<void()> readCallback;
    std::function<void()> writeCallback;
public:
    Channel(EventLoop *_loop,int _fd);
    ~Channel();

    void enableReading();
    void handleEvent();

    int getFd();
    uint32_t getEvents();
    uint32_t getRevents();
    bool getInEpoll();
    void setInEpoll(bool condition = true);
    void useET();
    void setRevents(uint32_t _ev);
    void setReadCallback(std::function<void()> _cb);
    void setUseThread(bool flag = true);
};

#endif
