#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include "src/util.h"
#include "src/InetAddress.h"
#include "src/Socket.h"
#include "src/Epoll.h"

#define BUFFER_SIZE 1024

int main(){
    Socket *sockfd = new Socket();

    InetAddress *cli_addr = new InetAddress("127.0.0.1", 9999);

    sockaddr_in addr = cli_addr->getAddr();
    if(connect(sockfd->getFd(), (struct sockaddr *)&addr, sizeof cli_addr->getAddr()) == -1){
        perror("connect");
        exit(1);
    }

    while(true){
        char buf[BUFFER_SIZE];
        memset(buf, 0, sizeof buf);
        std::cin>>buf;
        int len = send(sockfd->getFd(), buf, sizeof buf, 0);
        if(len == -1){
            std::cout<<"Disconnected.\n";
            break;
        }
        memset(buf, 0, sizeof buf);
        len = recv(sockfd->getFd(), buf, sizeof buf, 0);
        if(len > 0){
            std::cout<<"get info:"<<buf<<'\n';
        }
        else if(len == 0){
            std::cout<<"Disconnected\n";
            break;
        }
        else if(len == -1){
            close(sockfd->getFd());
            perror("recv");
        }
    }

    delete sockfd;
    delete cli_addr;

    return 0;
}
