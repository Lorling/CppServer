#ifndef __CONNECTION__
#define __CONNECTION__

#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
#include "Buffer.h"
#include <functional>
#include <cstring>

class Connection{
private:
    EventLoop * loop;
    Socket * sock;
    Channel * channel;
    std::function<void(int)> deleteConnection;
    Buffer * buff;
public:
    Connection(EventLoop * _loop, Socket * _sock) : loop(_loop), sock(_sock), channel(nullptr), buff(nullptr){
        channel = new Channel(loop, sock->getFd());
        channel->enableReading();
        channel->useET();
        std::function<void()> cb = std::bind(&Connection::echo, this, sock->getFd());
        channel->setReadCallback(cb);
        buff = new Buffer();
    }
    ~Connection(){
        delete channel;
        delete buff;
        delete sock;
    }
    void echo(int sockfd){
        char buf[1024];
        while(true){
            memset(&buf,0,sizeof buf);
            int len = recv(sockfd, buf, sizeof buf, 0); 
            if(len > 0){ 
                buff->append(buf, len);
                //std::cout<<buff->c_str();
            }
            else if(len == -1 && errno == EINTR){
                printf("continue\n");
                continue;
            }
            else if(len == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){
                printf("finish.from client : %d\n",sockfd);
                buff->clear();
                break;
            }
            else {
                printf("disconnction.\n");
                deleteConnection(sockfd);
                break;
            }
        }
    }
    void setDeleteConnection(std::function<void(int)> _cb) { deleteConnection = _cb;}
};

#endif
