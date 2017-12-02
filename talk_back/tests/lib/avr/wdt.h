
#ifndef AVR_WDT_
#define AVR_WDT_

#include<stdint.h>

#define _BV(name) name
#define ISR(name) void isr_##name()

extern uint8_t WDCE;
extern uint8_t WDRF;
extern uint8_t WDTO_8S;

void wdt_enable(int mode);
void wdt_disable();
void wdt_reset();

#endif //AVR_WDT_

