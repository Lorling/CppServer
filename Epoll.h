#ifndef  __SOMEFILE_H__
#define  __SOMEFILE_H__

#include <sys/epoll.h>
#include <vector>
#include "Channel.h"

class Epoll{
private:
    int epfd;
    struct epoll_event *events;
public:
    Epoll();
    ~Epoll();

    void addFd(int fd, uint32_t op);
    std::vector<Channel *> poll(int timeout = -1);

    void updateChannel(Channel*);
};

#endif
