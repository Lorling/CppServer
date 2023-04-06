#include "Buffer.h"
#include <iostream>

Buffer::Buffer(){
}

Buffer::~Buffer(){
}

void Buffer::clear(){
    buf.clear();
}

int Buffer::size(){
    return buf.size();
}

void Buffer::append(const char * _str, int _size){
    for(int i = 0; i < _size; i++){
        if(_str[i] == '\0') break;
        buf+=_str[i];
    }
}

const char * Buffer::c_str(){
    return buf.c_str();
}

void Buffer::getline(){
    buf.clear();
    std::getline(std::cin,buf);
}
