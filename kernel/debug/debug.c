#include "debug.h"
#include "print.h"
#include "interrupt.h"

void panic_spin(char *filename, int line, const char *func, const char *condition)
{
	intr_disable();
	put_str("!!!!!!  ERROR  !!!!!!\n");
	put_str("filename : "); put_str(filename); put_str("\n");
	put_str("line : 0x"); put_int(line); put_str("\n");
	put_str("function : "); put_int(func); put_str("\n");
	put_str("condition : "); put_int(condition); put_str("\n");
	while(1);
}