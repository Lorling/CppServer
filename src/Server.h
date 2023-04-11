#ifndef __SERVER__
#define __SERVER__

#include "Socket.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include "Connection.h"
#include <map>
#include <functional>

class Acceptor;
class Server{
private:
    EventLoop * loop;
    Acceptor * acceptor;
    std::map<int,Connection *> connections;
public:
    Server(EventLoop * _loop) : loop(_loop), acceptor(nullptr){
        acceptor = new Acceptor(loop);
        std::function<void(Socket *)> cb = std::bind(&Server::newConnection, this, std::placeholders::_1);
        acceptor->setNewConnectionCallback(cb);
    }
    ~Server(){ delete acceptor;}

    void newConnection(Socket * sock){//xin lianjie
        if(sock->getFd() != -1){
            Connection * conn = new Connection(loop, sock);
            std::function<void(int)> cb = std::bind(&Server::deleteConnection,this,std::placeholders::_1);
            conn->setDeleteConnection(cb);
            connections[sock->getFd()] = conn;
        }
    }
    void deleteConnection(int sockfd){
        if(sockfd != -1){
            auto t = connections.find(sockfd);
            if(t != connections.end())
                connections.erase(sockfd);
        }
    }
};

#endif
