#ifndef STRING_H
#define STRING_H
#include <stdint.h>
#include <stdio.h>

int strcmp(const char *s1, const char *s2);
int lowStrCmp(const char *s1, const char *s2);
void *memcpy(void *destination, const void *source, long unsigned int length);
long unsigned int strlen(const char *str);
const char *strchr(const char *s, int c);

#endif