#ifndef __ACCEPTOR__
#define __ACCEPTOR__

#include "Server.h"
#include "EventLoop.h"
#include "Socket.h"
#include "InetAddress.h"
#include "Channel.h"

class Acceptor{
private:
    EventLoop * loop;
    Socket * sock;
    InetAddress * addr;
    Channel * acceptChannel;
public:
    Acceptor(EventLoop*);
    ~Acceptor();

    std::function<void(Socket*)> newConnectionCallback;
    void setNewConnectionCallback(std::function<void(Socket*)>);
    void acceptConnection();
};

#endif
