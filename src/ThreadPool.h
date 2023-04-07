#ifndef __THREADPOOL__
#define __THREADPOOL__

#include <iostream>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <vector>
#include <future>
#include <utility>

template<typename T>
class SafeQueue{
private:
    std::queue<T> q;
    std::mutex m;
public:
    SafeQueue(){}
    ~SafeQueue(){
        delete & q;
        delete & m;
    }
    bool empty(){
        std::unique_lock<std::mutex> lock(m);
        return q.empty();
    }
    int size(){
        std::unique_lock<std::mutex> lock(m);
        return q.size();
    }
    void push(T & t){
        std::unique_lock<std::mutex> lock(m);
        q.push(t);
    }
    bool pop(T & t){
        std::unique_lock<std::mutex> lock(m);
        if(q.empty()) return false;
        t = std::move(q.front());
        q.pop();
        return true;
    }
};

class ThreadPool{
private:
    SafeQueue<std::function<void()>> tasks;
    std::vector<std::thread> threads;
    std::mutex m_task;
    std::condition_variable cv;
    bool shutdown;
public:
    ThreadPool(int size = 4);//cpu  nember
    ~ThreadPool();
    
    void shut(){
        //std::cout<<tasks.size();
        shutdown = true;
        cv.notify_all();
        for(auto & i : threads)
            if(i.joinable())
                i.join();
    }
    template<typename F,typename ...Args>
    auto submit(F && f, Args && ...args) -> std::future<decltype(f(args...))>{
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f),std::forward<Args>(args)...);
        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
        std::function<void()> warpper = [task_ptr](){
            (*task_ptr)();
        };
        tasks.push(warpper);
        cv.notify_one();
        return task_ptr->get_future();
    }
};

#endif
