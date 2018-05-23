#ifndef LIB_H
#define LIB_H

#include <stdint.h>
// C functions
void *memset(void *destination, int32_t character, uint64_t length);
void *memcpy(void *destination, const void *source, uint64_t length);
void *malloc(int64_t size);

//ASM functions
char *cpuVendor(char *result);
uint64_t get_time_RTC(uint64_t value);
void beep(void);

#endif