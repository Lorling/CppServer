#include "Server.h"
#include "Socket.h"
#include "Channel.h"
#include "InetAddress.h"
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <functional>

Server::Server(EventLoop * _loop) : loop(_loop), acceptor(nullptr){
    acceptor = new Acceptor(loop);
    std::function<void(Socket*)> cb = std::bind(&Server::newConnection,this,std::placeholders::_1);
    acceptor->setNewConnectionCallback(cb);
}

Server::~Server(){
    delete acceptor;
}

void Server::handleReadEvent(int sockfd){
    char buf[1024];
    while(true){
        memset(&buf, 0, sizeof buf);
        int len = recv(sockfd, buf, sizeof buf, 0);
        if(len > 0){
            printf("from fd %d\nget message:%s\n", sockfd, buf);
        } else if(len == 0){
            printf("fd %d disconnected\n", sockfd);
            close(sockfd);
            break;
        } else if(len == -1 && errno == EINTR){
            std::cout<<"continue...";
            continue; 
        } else if(len == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){
            printf("finish. errno:%d\n", errno);
            break;
        }
    }
}

void Server::newConnection(Socket * sock){
    Connection * con = new Connection(loop,sock);
    std::function<void()> cb = std::bind(&Server::deleteConnection, this, sock);
    con->setDeleteConnection(cb);
    connections[sock->getFd()] = con;
}

void Server::deleteConnection(Socket * sock){
    connections.erase(sock->getFd());
}
