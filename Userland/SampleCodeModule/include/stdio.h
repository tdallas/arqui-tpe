#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>
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
void printf(const char *str,...);
int sscanf(char *str, const char *format, ...);
int scanf(const char* format,...);
char* readLine();

#endif