#ifndef __SERVER__
#define __SERVER__

#include "Socket.h"
#include "EventLoop.h"

class Server{
private:
    EventLoop *loop;
public:
    Server(EventLoop *);
    ~Server();

    void handleReadEvent(int);//kedu shijian
    void newConnection(Socket * ser_sock);//xin lianjie
};

#endif
