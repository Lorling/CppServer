#ifndef __CHANNEL__
#define __CHANNEL__

#include <sys/epoll.h>

class Epoll;
class Channel{
private:
    Epoll * ep;
    int fd;
    uint32_t events;//xi wang jian ting de shi jian
    uint32_t revents;//zheng zai yun xing
    bool inEpoll;
public:
    Channel(Epoll *_ep,int _fd);
    ~Channel();

    void enableReading();

    int getFd();
    uint32_t getEvents();
    uint32_t getRevents();
    bool getInEpoll();
    void setInEpoll();

    void setRevents(uint32_t); 
};

#endif
