#include "ThreadPool.h"

ThreadPool::ThreadPool(int size) : threads(size), shutdown(false){
    for(auto & i :threads)
        i = std::thread([this](){
            std::function<void()> func;
            bool flag = false;
            while(true){
                {
                    std::unique_lock<std::mutex> lock(m_task);
                    if(tasks.empty()){
                        cv.wait(lock);
                    }
                    flag = tasks.pop(func);
                }
                if(flag)
                    func();
            }
        });
}

ThreadPool::~ThreadPool(){
    shutdown = true;
    cv.notify_all();
    for(auto & i : threads)
        if(i.joinable())
            i.join();
}
