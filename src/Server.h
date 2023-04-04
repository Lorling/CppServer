#ifndef __SERVER__
#define __SERVER__

#include "Socket.h"
#include "EventLoop.h"
#include "Acceptor.h"

class Acceptor;
class Server{
private:
    EventLoop *loop;
    Acceptor *acceptor;
public:
    Server(EventLoop *);
    ~Server();

    void handleReadEvent(int);//kedu shijian
    void newConnection(Socket * ser_sock);//xin lianjie
};

#endif
