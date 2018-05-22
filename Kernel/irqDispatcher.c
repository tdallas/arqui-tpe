#include <stdint.h>
#include <time.h>
#include <keyboardDriver.h>

static void int_20();
static void int_21();
static void (*ints[])() = { int_20 , int_21};

void irqDispatcher(uint64_t irq) {
	(*ints[irq])();
}

void int_20() {
	timer_handler();
}

void int_21(){
	keyboard_handler();
}