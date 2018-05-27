#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define EOF 0
#define NULL 0

uint64_t systemCall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
int getchar();
void putchar(char c);
void *malloc(long unsigned int size);
void free(void *pointer);
void printf(const char *str,...);

#endif