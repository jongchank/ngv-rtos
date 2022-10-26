#include "bsw.h"

ISR2(TimerISR)
{
	;
}

TASK(Task1) {
	printfSerial("Hello World\n");

	TerminateTask();
}
