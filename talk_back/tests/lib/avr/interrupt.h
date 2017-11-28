
#ifndef AVR_INTERRUPT_
#define AVR_INTERRUPT_

#define _BV(name) name
#define ISR(name) void isr_##name()

#define cli()
#define sei()

#endif //AVR_INTERRUPT_

