//Completar .h
#include <stdio.h>
#include <stdint.h>

int getchar()
{
    return systemCall(1, 0, 0, 0, 0, 0);
}

void putchar(char c)
{
    if(c!=0)
        systemCall(2, (uint64_t)c, 0, 0, 0, 0);
}

void *malloc(long unsigned int size){
    return (void *)systemCall(4, (uint64_t)size, 0, 0, 0, 0);
}