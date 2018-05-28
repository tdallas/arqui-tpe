#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <systemCall.h>

#define EOF 0
#define NULL 0

int abs(int a);
int getchar();
void putchar(char c);
void *malloc(long unsigned int size);
void free(void *pointer);
int printf(const char *str, ...);
int vprintf(const char *str, va_list arguments);
int sscanf(const char *str, const char *format, ...);
int scanf(const char *format, ...);
int vsscanf(const char *str, const char *format, va_list args);
void readLine(char *buff);

#endif