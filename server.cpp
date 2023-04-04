#include "src/EventLoop.h"
#include "src/Server.h"

int main(){
    EventLoop * ser_loop = new EventLoop();
    Server * ser = new Server(ser_loop);
    ser_loop->loop();

    return 0;
}
