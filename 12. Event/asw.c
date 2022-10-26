#include "bsw.h"

ISR2(TimerISR)
{
    static long c = -4;
    IncrementCounter(counter1);
    printfSerial("\n%4ld: ", c++);
}

ISR2(ButtonISR)
{
    int a0;
	DisableAllInterrupts();
	if ((PINC & 0x01) != 0) return;
	printfSerial("<BUTTON ISR>");
    a0 = analogRead(A0); // read ADC value
    if (a0 < 50) {	// UP
        SetEvent(Task2, Event1);
    } else if (a0 < 200) { // DOWN
        SetEvent(Task2, Event2);
    } else if (a0 < 380) { // LEFT
        ;
    } else if (a0 < 520) { // RIGHT
        ;
    }
	EnableAllInterrupts();
}

ALARMCALLBACK(MyCallback) {
	// printfSerial("<MyCallback>");
}

TASK(Task1)
{
	printfSerial("Task1 Begins...");
	mdelay(3000);
	printfSerial("Task1 Finishes...");
	TerminateTask();
}

TASK(Task2)
{
	EventMaskType mask;
	printfSerial("Task2 Begins...");
	printfSerial("Task2 Waits...");
	WaitEvent(Event1 | Event2);
	printfSerial("Task2 Wakes Up...");
	GetEvent(Task2, &mask);
	if (mask & Event1) {
	    printfSerial("[Event1]");
	    ClearEvent(Event1);
	}
	if (mask & Event2) {
	    printfSerial("[Event2]");
	    ClearEvent(Event2);
	}

	printfSerial("Task2 Waits...");
	WaitEvent(Event1 | Event2);
	printfSerial("Task2 Wakes Up...");

	printfSerial("Task2 Finishes...");
	TerminateTask();
}
