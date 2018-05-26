#ifndef STRING_H
#define STRING_H
#include <stdint.h>

int strcmp(char *str1, char *str2);
void * memcpy(void *destination, const void *source, long unsigned int length);
long unsigned int strlen(const char *str);

#endif