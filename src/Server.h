#ifndef __SERVER__
#define __SERVER__

#include "Socket.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include "Connection.h"
#include "ThreadPool.h"
#include <map>
#include <functional>
#include <vector>

class Acceptor;
class Server{
private:
    EventLoop * mainReactor;
    Acceptor * acceptor;
    std::map<int,Connection *> connections;
    std::vector<EventLoop *> subReactors;
    ThreadPool * pool;
public:
    Server(EventLoop * _loop) : mainReactor(_loop), acceptor(nullptr), pool(nullptr){
        acceptor = new Acceptor(mainReactor);
        std::function<void(Socket *)> cb = std::bind(&Server::newConnection, this, std::placeholders::_1);
        acceptor->setNewConnectionCallback(cb);

        int size = std::thread::hardware_concurrency();
        pool = new ThreadPool(size);
        for(int i = 0; i < size; i++)
            subReactors.push_back(new EventLoop());

        for(int i = 0; i < size; i++){
            std::function<void()> sub_loop = std::bind(&EventLoop::loop, subReactors[i]);
            pool->submit(sub_loop);
        }
    }
    ~Server(){
        delete acceptor;
        delete pool;
    }

    void newConnection(Socket * sock){//xin lianjie
        if(sock->getFd() != -1){
            int random = sock->getFd() % subReactors.size();
            Connection * conn = new Connection(subReactors[random], sock);
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
