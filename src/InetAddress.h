#ifndef __INETADDRESS__
#define __INETADDRESS__

#include <arpa/inet.h>

class InetAddress{
private:
    struct sockaddr_in addr;
    socklen_t addr_len;
public:
    InetAddress();
    InetAddress(const char *ip, uint16_t port);
    ~InetAddress();

    void setInetAddr(sockaddr_int _addr,socklen_t _addr_len();
    sockaadr_in getAddr();
    socklen_t getAddr_len();
};

#endif
