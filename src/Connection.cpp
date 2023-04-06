#include "Connection.h"
#include <cstring>

Connection::Connection(EventLoop * _loop, Socket * _sock) : loop(_loop), sock(_sock){
    channel = new Channel(loop, sock->getFd());
    std::function<void()> cb = std::bind(&Connection::echo, this, sock->getFd());
    channel->setCallback(cb);
    channel->enableReading();
}

Connection::~Connection(){
    delete sock;
    delete channel;
}

void Connection::setDeleteConnection(std::function<void()> _cb){
    deleteConnection = _cb;
}

void Connection::echo(int sockfd){
    char buf[1024];
    while(true){
        memset(&buf,0,sizeof buf);
        int len = recv(sockfd, buf, sizeof buf, 0);
        if(buf > 0){
            printf("get message : %s\nfrom : %d\n", buf, sockfd);
        }
        else if(len == -1 && errno == EINTR){
            printf("continue\n");
            break;
        }
        else if(len == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){
            printf("finish.errno : %d\n",errno);
            break;
        }
        else {
            printf("disconnction.\n");
            break;
        }
    }
}
