//Completar .h
#include <string.h>

long unsigned int strlen(const char *str) {
    int count = 0;
    while (*str != '\0') {
        count++;
        str++;
    }
    return count;
}