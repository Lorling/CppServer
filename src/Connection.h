#ifndef __CONNECTION__
#define __CONNECTION__

#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
#include "Buffer.h"
#include <functional>
#include <cstring>

class Connection{
private:
    EventLoop * loop;
    Socket * sock;
    Channel * channel;
    std::function<void()> deleteConnection;
    Buffer * buff;
public:
    Connection(EventLoop*, Socket*);
    ~Connection();

    void echo(int);
    void setDeleteConnection(std::function<void()>);
};

#endif
