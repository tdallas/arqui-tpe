#ifndef STDIO_H
#define STDIO_H

#define EOF 0
#define NULL 0

int getchar();
void putchar(char c);
void *malloc(long unsigned int size);
void printf(const char *str,...);

#endif