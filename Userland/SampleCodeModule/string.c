//Completar .h
#include <string.h>

size_t strlen(const char *str) {
    int count = 0;
    while (*str != null || *str != '\0') {
        count++;
    }
    return count;
}