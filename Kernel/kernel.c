#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <idtLoader.h>
#include <time.h>
#include <videoDriver.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void *const sampleCodeModuleAddress = (void *)0x400000;
static void *const sampleDataModuleAddress = (void *)0x500000;

typedef int (*EntryPoint)();

void clearBSS(void *bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void *getStackBase()
{
	return (void *)((uint64_t)&endOfKernel + PageSize * 8 //The size of the stack itself, 32KiB
					- sizeof(uint64_t)					  //Begin at the top of the stack
	);
}

void *initializeKernelBinary()
{
	char buffer[10];

	printString("[x64BareBones]", 255, 255, 255);
	writeChar('\n', 255, 255, 255);

	printString("CPU Vendor:", 255, 255, 255);
	printString(cpuVendor(buffer), 255, 255, 255);
	writeChar('\n', 255, 255, 255);

	printString("[Loading modules]", 255, 255, 255);
	writeChar('\n', 255, 255, 255);
	void *moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress};

	loadModules(&endOfKernelBinary, moduleAddresses);
	printString("[Done]", 255, 255, 255);
	writeChar('\n', 255, 255, 255);
	writeChar('\n', 255, 255, 255);

	printString("[Initializing kernel's binary]", 255, 255, 255);
	writeChar('\n', 255, 255, 255);

	clearBSS(&bss, &endOfKernel - &bss);

	printString("  text: 0x", 255, 255, 255);
	printHex((uint64_t)&text);
	writeChar('\n', 255, 255, 255);
	printString("  rodata: 0x", 255, 255, 255);
	printHex((uint64_t)&rodata);
	writeChar('\n', 255, 255, 255);
	printString("  data: 0x", 255, 255, 255);
	printHex((uint64_t)&data);
	writeChar('\n', 255, 255, 255);
	printString("  bss: 0x", 255, 255, 255);
	printHex((uint64_t)&bss);
	writeChar('\n', 255, 255, 255);

	printString("[Done]", 255, 255, 255);
	writeChar('\n', 255, 255, 255);
	writeChar('\n', 255, 255, 255);
	return getStackBase();
}

int main()
{
	printString("[IDT Loader]", 255, 255, 255);
	writeChar('\n', 255, 255, 255);

	printString("  Loading instructions...", 255, 255, 255);
	load_idt(); //Carga instrucciones
	printString("  Done.", 255, 255, 255);
	
	writeChar('\n', 255, 255, 255);
	printString("[Finished]", 255, 255, 255);
	writeChar('\n', 255, 255, 255);
	writeChar('\n', 255, 255, 255);

	printString("[Kernel Main]", 255, 255, 255);
	writeChar('\n', 255, 255, 255);
	printString("  Sample code module at 0x", 255, 255, 255);
	printHex((uint64_t)sampleCodeModuleAddress);
	writeChar('\n', 255, 255, 255);

	printString("  Sample data module at 0x", 255, 255, 255);
	printHex((uint64_t)sampleDataModuleAddress);
	writeChar('\n', 255, 255, 255);

	printString("[Finished]", 255, 255, 255);
	writeChar('\n', 255, 255, 255);
	writeChar('\n', 255, 255, 255);

	printString("System booting in 2 seconds...", 255, 255, 255);
	seconds_delay(2);
	clearScreen();
	speakerBeep();

	((EntryPoint)sampleCodeModuleAddress)();

	return 0;
}