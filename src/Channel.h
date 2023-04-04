#ifndef __CHANNEL__
#define __CHANNEL__

#include <sys/epoll.h>
#include <functional>

class EventLoop;
class Channel{
private:
    EventLoop * loop;
    int fd;
    uint32_t events;//xi wang jian ting de shi jian
    uint32_t revents;//zheng zai yun xing
    bool inEpoll;
    std::function<void()> callback;
public:
    Channel(EventLoop *_loop,int _fd);
    ~Channel();

    void enableReading();
    void handleEvent();

    int getFd();
    uint32_t getEvents();
    uint32_t getRevents();
    bool getInEpoll();
    void setInEpoll();

    void setRevents(uint32_t); 
    void setCallback(std::function<void()>);
};

#endif
