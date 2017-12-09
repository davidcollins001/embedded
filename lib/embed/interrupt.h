
#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <avr/interrupt.h>
#include <avr/io.h>

#include "defs.h"

extern uint8_t FLAG;

void init_interrupt(void);
void toggle_interrupt(toggle_t choice);

// ISRs get created for tests so add prototypes
#ifdef TEST
void isr_PCINT2_vect();
#endif

#endif //INTERRUPT_H_

