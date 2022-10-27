#include "bsw.h"

ISR2(TimerISR)
{
    static long c = -5;
    IncrementCounter(counter1);
    printfSerial("\n%4ld: ", ++c);
}

TASK(TaskH)
{
	printfSerial("<TaskH begins.> ");

	printfSerial("<TaskH ends.> ");
    TerminateTask();
}

TASK(TaskL)
{
	printfSerial("<TaskL begins.> ");

	printfSerial("TaskL waits. ");
	WaitEvent(Event1);
	printfSerial("TaskL wakes up. ");

	printfSerial("<TaskL ends.> ");
	TerminateTask();
}
