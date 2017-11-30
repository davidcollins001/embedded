
#ifndef AVR_WDT_
#define AVR_WDT_

#define _BV(name) name
#define ISR(name) void isr_##name()

extern unsigned char WDCE;
extern unsigned char WDRF;
extern unsigned char WDTO_8S;

void wdt_enable(int mode);
void wdt_disable();
void wdt_reset();

#endif //AVR_WDT_

