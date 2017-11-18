
#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <avr/interrupt.h>
#include <avr/io.h>

extern unsigned char FLAG;

void init_pcint2(void);

#endif //INTERRUPT_H_

