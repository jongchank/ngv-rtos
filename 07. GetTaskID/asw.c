#include "bsw.h"

ISR2(TimerISR)
{
    static long c = -4;
    if (c == 0)
    	ActivateTask(Task1);
    printfSerial("\n%4ld: ", c++);
}

TASK(Task1)
{
	TaskType id;
	printfSerial("Task1 Begins...");
	mdelay(3000);
	ActivateTask(Task2);
	mdelay(3000);
	GetTaskID(&id);
	printfSerial("Task ID = %d...", id);
	printfSerial("Task1 Finishes...");
	TerminateTask();
}

TASK(Task2)
{
	TaskType id;
	printfSerial("Task2 Begins...");
	mdelay(3000);
	GetTaskID(&id);
	printfSerial("Task ID = %d...", id);
	printfSerial("Task2 Finishes...");
	TerminateTask();
}
