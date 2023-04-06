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

void Socket::bind(InetAddress * _addr){
    struct sockaddr_in addr = _addr->getAddr();
    socklen_t len = _addr->getAddr_len();
    errif(::bind(fd, (struct sockaddr*)&addr, len) == -1, "bind");
}

void Socket::listen(){
    errif(::listen(fd, 20) == -1, "listen");
}

void Socket::setnonblocking(){
    fcntl(fd, F_SETFL, (fcntl(fd, F_GETFL) | O_NONBLOCK));
}

int Socket::accept(InetAddress * _addr){
    struct sockaddr_in addr = _addr->getAddr();
    socklen_t len = _addr->getAddr_len();
    int cli_sockfd = ::accept(fd, (struct sockaddr *)&addr, &len);
    errif(cli_sockfd == -1, "accept");
    return cli_sockfd;
}

int Socket::getFd(){
    return fd;
}
