#ifndef __SOCKET__
#define __SOCKET__

#include "InetAddress.h"

class Socket{
private:
    int fd;
public:
    Socket();
    Socket(int);
    ~Socket();

    void bind(InetAddress *);
    void listen();
    void setnonblocking();

    int accept(InetAddress *);

    int getFd();
};

#endif
