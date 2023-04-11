#ifndef __ACCEPTOR__
#define __ACCEPTOR__

#include "Server.h"
#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"

class Acceptor{
private:
    EventLoop * loop;
    Socket * sock;
    Channel * acceptChannel;
    std::function<void(Socket *)> newConnectionCallback;
public:
    Acceptor(EventLoop * _loop) : loop(_loop), sock(nullptr), acceptChannel(nullptr){
        sock = new Socket();
        InetAddress * addr = new InetAddress("127.0.0.1", 9999);
        sock->bind(addr);
        sock->listen();
        acceptChannel = new Channel(loop, sock->getFd());
        std::function<void()> cb = std::bind(&Acceptor::acceptConnection, this);
        acceptChannel->setReadCallback(cb);
        acceptChannel->enableReading();
        delete addr;
    }
    ~Acceptor(){
        delete sock;
        delete acceptChannel;
    }

    void setNewConnectionCallback(std::function<void(Socket*)> func){ newConnectionCallback = func;}
    void acceptConnection(){
        InetAddress * addr = new InetAddress();
        Socket * cli_sock = new Socket(sock->accept(addr));
        printf("new client : %d\nIP : %s Port : %d\n", cli_sock->getFd(), inet_ntoa(addr->getAddr().sin_addr), ntohs(addr->getAddr().sin_port));
        cli_sock->setnonblocking();
        newConnectionCallback(cli_sock);
        delete addr;
    }
};

#endif
