//Completar .h
#include <stdio.h>
#include <stdint.h>

char getChar()
{
    char c[1];
    systemCall(1, (uint64_t)c, 0, 0, 0, 0);
    return c[0];
}

void putChar(char c)
{
    if(c!=0)
        systemCall(2, (uint64_t)c, 0, 0, 0, 0);
}