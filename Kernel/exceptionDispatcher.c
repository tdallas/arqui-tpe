#include <videoDriver.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_CODE_EXCEPTION_ID 6

static void zero_division();
static void invalid_op_code();

void exceptionDispatcher(int exception)
{
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	else if (exception == INVALID_OP_CODE_EXCEPTION_ID)
		invalid_op_code();
}

static void zero_division()
{
	printString("ERROR: Division by zero exception.", 255, 255, 255);
}

static void invalid_op_code()
{
	printString("ERROR: Invalid opcode exception.", 255, 255, 255);
}