#include <iostream>
#include "src/ThreadPool.h"

void print(int a, double b, const char * c, std::string d){
    std::cout<<a<<" "<<b<<' '<<c<<" " <<d<<"\n";
}

void test(){
    std::cout<<"yeah~\n";
}

int main(){
    ThreadPool * pool = new ThreadPool(1);
    std::function<void()> func = std::bind(print,1, 3.14, "hello", "world");
    auto res1 = pool->submit(func);
    res1.get();
    func = test;
    auto res2 = pool->submit(func);
    res2.get();
    delete pool;
    return 0;
}
