
#ifndef _AVR_WDT_H_
#define _AVR_WDT_H_

#include<stdint.h>

#define ISR(name) void isr_##name()

extern uint8_t WDCE;
extern uint8_t WDRF;
extern uint8_t WDTO_8S;

void wdt_enable_int(int mode);
void wdt_disable();
void wdt_reset();

#endif //_AVR_WDT_H_

