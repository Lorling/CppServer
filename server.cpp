#include <iostream>
#include <cstring>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <vector>
#include "util.h"
#include "Epoll.h"
#include "InetAddress.h"
#include "Socket.h"

void handleReadEvent(int sockfd){
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


int main(){
    Socket *sockfd = new Socket();

    InetAddress *ser_addr = new InetAddress("127.0.0.1", 9999);

    sockfd->bind(ser_addr);
    sockfd->listen();

    Epoll *epfd = new Epoll();
    sockfd->setnonblocking();
    epfd->addFd(sockfd->getFd(), EPOLLIN | EPOLLET);

    while(true){
        std::vector<epoll_event> events = epfd->poll();
        int nfds = events.size();
        for(int i = 0; i < nfds; i++){
            if(events[i].data.fd == sockfd->getFd()){
                InetAddress *cli_addr = new InetAddress();
                Socket *cli_sockfd = new Socket(sockfd->accept(cli_addr));
                printf("new client:%d\nIP:%s Port:%d",cli_sockfd->getFd(), inet_ntoa(cli_addr->addr.sin_addr), ntohs(cli_addr->addr.sin_port));
                cli_sockfd->setnonblocking();
                epfd->addFd(cli_sockfd->getFd(),EPOLLIN | EPOLLET);
            } else if(events[i].events & EPOLLIN){
                    handleReadEvent(events[i].data.fd);
            } else{
                std::cout<<"nothing\n";
            }
        }
    }

    delete ser_addr;
    delete sockfd;
    delete epfd;

    return 0;
}
