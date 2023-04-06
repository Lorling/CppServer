#ifndef __BUFFER__
#define __BUFFER__

#include <string>

class Buffer{
private:
    std::string buf;
public:
    Buffer();
    ~Buffer();
    
    void append(const char * _str,int _size);
    int size();
    const char * c_str(); //string -> char
    void clear();
    void getline();
};

#endif
