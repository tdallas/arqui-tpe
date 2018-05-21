#include <time.h>
#include <stdint.h>

static void int_20();

void irqDispatcher(uint64_t irq) {
	void (*idts[])() = { int_20 };
	(*idts[irq])();
	return;
}

void int_20() {
	timer_handler();
}