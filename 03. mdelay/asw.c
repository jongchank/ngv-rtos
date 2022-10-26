#include "bsw.h"

ISR2(TimerISR)
{
	;
}

TASK(Task1)
{
	printfSerial("Hello World\n");

	mdelay(3000);

	printfSerial("Goodbye World\n");
	TerminateTask();
}
