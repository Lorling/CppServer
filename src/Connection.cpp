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
        if(len > 0){
            buff->append(buf, len);
        }
        else if(len == -1 && errno == EINTR){
            printf("continue\n");
            continue;
        }
        else if(len == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){
            printf("finish.from client : %d\n",sockfd);
            break;
        }
        else {
            printf("disconnction.\n");
            deleteConnection();
            break;
        }
    }
}
