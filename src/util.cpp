#include "util.h"
#include <iostream>

void errif(bool condition,const char *errmsg){
    if(condition){
        perror(errmsg);
        exit(1);
    }
}
