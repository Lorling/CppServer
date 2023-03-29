#include "Socket.h"
#include "InetAddress.h"
#include "util.h"
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

Socket::Socket() : fd(-1){
    fd = socket(AF_INET, SOCK_STREAM, 0);
    errif(fd == -1, "socket");
}

Socket::Socket(int _fd) : fd(_fd){
    errif(fd == -1, "socket");
}

Socket::~Socket(){
    if(fd != -1){
        close(fd);
        fd = -1;
    }
}

void Socket::bind(InetAddress * addr){
    errif(::bind(fd, (struct sockaddr*)&addr->addr, addr->addr_len) == -1, "bind");
}

void Socket::listen(){
    errif(::listen(fd, 20) == -1, "listen");
}

void Socket::setnonblocking(){
    fcntl(fd, F_SETFL, (fcntl(fd, F_GETFL) | O_NONBLOCK));
}

int Socket::accept(InetAddress * addr){
    int cli_sockfd = ::accept(fd, (struct sockaddr *)&addr->addr, &addr->addr_len);
    errif(cli_sockfd == -1, "accept");
    return cli_sockfd;
}

int Socket::getFd(){
    return fd;
}
