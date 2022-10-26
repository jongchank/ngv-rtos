#ifndef BSW_H_
#define BSW_H_

#include "ee.h"
#include "Arduino.h"

#ifdef __cplusplus
extern "C"{
#endif

void mdelay(unsigned long delay_ms);

void printfSerial(const char *fmt, ... );

#ifdef __cplusplus
}
#endif

#endif /* BSW_H_ */
