#ifndef __INETADDRESS__
#define __INETADDRESS__

#include <arpa/inet.h>
#include <cstring>

class InetAddress{
private:
    struct sockaddr_in addr;
public:
    InetAddress(){
        memset(&addr, 0, sizeof addr);
    }
    InetAddress(const char *ip, uint16_t port){
        memset(&addr, 0, sizeof addr);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip);
        addr.sin_port = htons(port);
    }
    ~InetAddress(){}

    void setInetAddr(sockaddr_in _addr){addr = _addr;}
    sockaddr_in getAddr(){
        return addr;
    }
};

#endif
