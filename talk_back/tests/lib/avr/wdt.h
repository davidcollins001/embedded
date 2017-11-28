
#ifndef AVR_WDT_
#define AVR_WDT_

#define _BV(name) name
#define ISR(name) void isr_##name()

extern unsigned char WDCE;

void wdt_enable(int mode);
void wdt_disable();

#endif //AVR_WDT_

