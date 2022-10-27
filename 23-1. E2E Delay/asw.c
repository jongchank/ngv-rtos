#include "bsw.h"

#define UP 		1
#define DOWN 	-1

#define OUT(in)	(in == UP ? "UP" : (in == DOWN ? "DOWN" : "NA"))

int R1_in;
int R2_in;
int R3_in;
int R3_out;

void Runnable_1(void)
{
	R2_in = R1_in;
}

void Runnable_2(void)
{
	R3_in = R2_in;
}

void Runnable_3(void)
{
	R3_out = R3_in;
}

ISR2(TimerISR)
{
    static long c = -5;
    char *out = "NA";
    IncrementCounter(counter1);
    if (R3_out == UP)
    	out = "UP";
    else if (R3_out == DOWN)
    	out = "DN";

    printfSerial("\n%4ld: [%s] ", ++c, out);
}

ISR2(ButtonISR)
{
    int a0;
	DisableAllInterrupts();
	if ((PINC & 0x01) != 0) return;

    a0 = analogRead(A0); // read ADC value
    if (a0 < 50) {	// UP
    	R1_in = UP;
    	printfSerial("<BUTTON UP>");
    } else if (a0 < 200) { // DOWN
    	R1_in = DOWN;
    	printfSerial("<BUTTON DOWN>");
    } else if (a0 < 380) { // LEFT
        ;
    } else if (a0 < 520) { // RIGHT
        ;
    }
	EnableAllInterrupts();
}

TASK(Task_2s)
{
	printfSerial("Task_2s begins... ");

	printfSerial("Task_2s finishes... ");
    TerminateTask();
}

TASK(Task_4s)
{
	printfSerial("Task_4s begins... ");

	printfSerial("Task_4s finishes... ");
	TerminateTask();
}

TASK(Task_8s)
{
	printfSerial("Task_8s begins... ");
	Runnable_1();
	Runnable_2();
	Runnable_3();
	printfSerial("Task_4s finishes... ");
	TerminateTask();
}
