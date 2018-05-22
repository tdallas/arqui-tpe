#include <stdint.h>
#include <keyboardDriver.h>
#include <videoDriver.h>
#include <lib.h>

uint64_t getTime(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

static uint64_t (*systemCall[])(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) = { getTime };

uint64_t systemCallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	return (*systemCall[rdi])(rsi, rdx, rcx, r8, r9);
}

uint64_t getTime(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	return get_time_RTC(rsi);
}
