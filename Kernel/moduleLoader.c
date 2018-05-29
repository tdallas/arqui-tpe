#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <videoDriver.h>

static void loadModule(uint8_t **module, void *targetModuleAddress);
static uint32_t readUint32(uint8_t **address);

void loadModules(void *payloadStart, void **targetModuleAddress)
{
	int i;
	uint8_t *currentModule = (uint8_t *)payloadStart;
	uint32_t moduleCount = readUint32(&currentModule);

	for (i = 0; i < moduleCount; i++)
		loadModule(&currentModule, targetModuleAddress[i]);
}

static void loadModule(uint8_t **module, void *targetModuleAddress)
{
	uint32_t moduleSize = readUint32(module);

	printString("  Will copy module at 0x", 255, 255, 255);
	printHex((uint64_t)*module);
	printString(" to 0x", 255, 255, 255);
	printHex((uint64_t)targetModuleAddress);
	printString(" (", 255, 255, 255);
	printHex(moduleSize);
	printString(" bytes)", 255, 255, 255);

	memcpy(targetModuleAddress, *module, moduleSize);
	*module += moduleSize;

	printString(" [Done]", 255, 255, 255);
	writeChar('\n', 255, 255, 255);
}

static uint32_t readUint32(uint8_t **address)
{
	uint32_t result = *(uint32_t *)(*address);
	*address += sizeof(uint32_t);
	return result;
}
