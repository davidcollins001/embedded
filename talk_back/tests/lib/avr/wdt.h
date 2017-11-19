
#ifndef AVR_WDT_
#define AVR_WDT_

#define _BV(name) name
#define ISR(name) void isr_##name()

int wdt_enable(int mode);
int wdt_disable();

#endif //AVR_WDT_

