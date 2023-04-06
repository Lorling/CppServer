#include "Acceptor.h"

Acceptor::Acceptor(EventLoop * _loop) : loop(_loop){
    sock = new Socket();
    addr = new InetAddress("127.0.0.1",9999);
    sock->bind(addr);
    sock->listen();
    sock->setnonblocking();
    acceptChannel = new Channel(loop, sock->getFd());
    std::function<void()> cb = std::bind(&Acceptor::acceptConnection,this);
    acceptChannel->setCallback(cb);
    acceptChannel->enableReading();
}

Acceptor::~Acceptor(){
    delete sock;
    delete acceptChannel;
}

void Acceptor::setNewConnectionCallback(std::function<void(Socket*)> _cb){
    newConnectionCallback = _cb;
}

void Acceptor::acceptConnection(){
    InetAddress * cli_addr = new InetAddress();
    Socket * cli_sock = new Socket(sock->accept(cli_addr));
    printf("new client : %d\nIP : %s Port : %d\n", cli_sock->getFd(), inet_ntoa(cli_addr->getAddr().sin_addr), ntohs(cli_addr->getAddr().sin_port));
    cli_sock->setnonblocking();
    newConnectionCallback(sock);
    delete cli_addr;
}
