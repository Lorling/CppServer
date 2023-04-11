#ifndef __SOCKET__
#define __SOCKET__

#include "InetAddress.h"
#include "util.h"
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>

class Socket{
private:
    int fd;
public:
    Socket(){
        fd = socket(AF_INET, SOCK_STREAM, 0);
        errif(fd == -1, "sockfd create");
    }

    Socket(int _fd) : fd(_fd){
        errif(fd == -1, "sockfd create2");
    }

    ~Socket(){
        if(fd != -1){
            close(fd);
            fd = -1;
        }
    }

    void bind(InetAddress * _addr){
        struct sockaddr_in addr = _addr->getAddr();
        errif(::bind(fd, (struct sockaddr *) &addr, sizeof addr) == -1, "bind");
    }
    void listen(){
        errif(::listen(fd, SOMAXCONN) == -1, "listen");
    }
    void setnonblocking(){
        fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
    }

    int accept(InetAddress * _addr){
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof addr);
        socklen_t len = sizeof addr;
        int cli_sockfd = ::accept(fd, (struct sockaddr*)&addr, &len);
        errif(cli_sockfd == -1, "accept");
        _addr->setInetAddr(addr);
        return cli_sockfd;
    }

    void connect(InetAddress * _addr){
        struct sockaddr_in addr = _addr->getAddr();
        errif(::connect(fd, (struct sockaddr*)&addr, sizeof addr) == -1, "connect");
    }

    int getFd(){
        return fd;
    }
};

#endif
