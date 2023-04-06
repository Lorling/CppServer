#ifndef __SERVER__
#define __SERVER__

#include "Socket.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include "Connection.h"
#include <map>

class Acceptor;
class Server{
private:
    EventLoop *loop;
    Acceptor *acceptor;
    std::map<int,Connection *> connections;
public:
    Server(EventLoop *);
    ~Server();

    void handleReadEvent(int);//kedu shijian
    void newConnection(Socket * sock);//xin lianjie
    void deleteConnection(Socket * sock);
};

#endif
