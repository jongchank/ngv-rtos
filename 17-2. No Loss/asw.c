#include "bsw.h"

volatile unsigned long shared = 0;

ISR2(TimerISR)
{
    IncrementCounter(counter1);
}

TASK(Task1)
{
	TaskType id;
	printfSerial("Task1 Begins...\n");

	for (unsigned long i = 0; i < 1000000; i++) {
		GetResource(S1);
		shared++;
		ReleaseResource(S1);
	}
	printfSerial("Added 1000000 to shared\n");
	printfSerial("counter = %lu\n", shared);
	printfSerial("Task1 Finishes...\n");
	TerminateTask();
}

TASK(Task2)
{
	static unsigned long i = 0;
    if (i < 1000) {
		GetResource(S1);
    	shared++;
    	ReleaseResource(S1);
    }
    else if (i == 1000) {
    	printfSerial("Added 1000 to shared\n");
    }
    else {
    	;
    }
	i++;
    TerminateTask();
}
