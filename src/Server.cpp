#include "Server.h"
#include "Socket.h"
#include "Channel.h"
#include "InetAddress.h"
#include <cstring>
#include <iostream>
#include <unistd.h>

Server::Server(EventLoop * _loop) : loop(_loop){
    Socket * ser_sock = new Socket();
    InetAddress *ser_addr = new InetAddress("127.0.0.1",9999);
    ser_sock->bind(ser_addr);
    ser_sock->listen();
    ser_sock->setnonblocking();

    Channel * ser_channel = new Channel(loop, ser_sock->getFd());
    std::function<void()> cb = std::bind(&Server::newConnection,this, ser_sock);
    ser_channel->setCallback(cb);
    ser_channel->enableReading();
}

Server::~Server(){
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

void Server::newConnection(Socket * ser_sock){
    InetAddress * cli_addr = new InetAddress;
    Socket * cli_sock = new Socket(ser_sock->accept(cli_addr));
    printf("new client : %d\nIP:%s Port:%d\n",cli_sock->getFd(),inet_ntoa(cli_addr->addr.sin_addr), ntohs(cli_addr->addr.sin_port));
    cli_sock->setnonblocking();
    Channel * cli_channel = new Channel(loop, cli_sock->getFd());
    std::function<void()> cb = std::bind(&Server::handleReadEvent, this, cli_sock->getFd());
    cli_channel->setCallback(cb);
    cli_channel->enableReading();
}
