
#ifndef AVR_INTERRUPT_
#define AVR_INTERRUPT_

#define _BV(name) name
#define ISR(name) void isr_##name()

#endif //AVR_INTERRUPT_

