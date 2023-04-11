#ifndef __BUFFER__
#define __BUFFER__

#include <string>
#include <iostream>

class Buffer{
private:
    std::string buf;
public:
    Buffer(){}
    ~Buffer(){}
    
    void append(const char * _str,int _size){
        for(int i = 0;i<_size;i++){
            if(_str[i] == '\0') break;
            buf.push_back(_str[i]);
        }
    }
    int size(){
        return buf.size();
    }
    const char * c_str(){ //string -> char
        return buf.c_str();
    }
    void clear(){
        buf.clear();
    }
    void getline(){
        buf.clear();
        std::getline(std::cin, buf);
    }
    void setBuf(const char * _buf){
        buf.clear();
        buf.append(_buf);
    }
};

#endif
