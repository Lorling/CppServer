#include <iostream>
#include "src/ThreadPool.h"

void print(int a, double b, const char * c, std::string d){
    std::cout<<a<<" "<<b<<' '<<c<<" " <<d<<"\n";
}

void test(){
    std::cout<<"yeah~\n"<<std::endl;
}

int main(){
    ThreadPool * pool = new ThreadPool();
    std::function<void()> func = std::bind(print,1, 3.14, "hello", "world");
    pool->submit(func);
    func = test;
    pool->submit(func);
    pool->shut();
    return 0;
}
