#include "ee.h"
#include "Arduino.h"
#include "bsw.h"

#define TIMER1_US	1000000U	/* 1 sec */

#define LEN_BUF 128

extern "C"{

void mdelay(unsigned long delay_ms)
{
	unsigned long prev_ms = millis(), current_ms = millis();
	unsigned long period_ms = 20, cnt = 0;
	while (cnt < (delay_ms / period_ms)) {
		current_ms = millis();
		if (current_ms - prev_ms >= period_ms) {
			cnt++;
			prev_ms = millis();
		}
	}
}

void printfSerial(const char *fmt, ... )
{
    char buf[LEN_BUF];
    va_list args;
    va_start (args, fmt );
    vsnprintf(buf, LEN_BUF, fmt, args);
    va_end (args);
    Serial.print(buf);
}

} /* extern "C" */

void loop(void)
{
	;
}

void setup(void)
{
	Serial.begin(9600);
	OsEE_atmega_startTimer1(TIMER1_US);
}

#define  _BV(bit) (1 << (bit))	// <<--
int main(void)
{
	PORTC = _BV(PC0); // PC0 == PA0
	PCICR = _BV(PCIE1);   //PCIE1
	PCMSK1 = _BV(PCINT8);  //PCINT8
	EIFR = 0xff;
	sei();

	init();

#if defined(USBCON)
	USBDevice.attach();
#endif
	
	setup();

	printfSerial("\n...............\n");
	printfSerial("...OS Starts...\n");
	printfSerial("...............\n");

	StartOS(OSDEFAULTAPPMODE);	/* never returns */

	return 0;
}
