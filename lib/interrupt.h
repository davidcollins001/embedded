
#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <avr/interrupt.h>
#include <avr/io.h>

#include "defs.h"

extern uint8_t FLAG;

void init_interrupt(void);
void toggle_interrupt(toggle_t choice);

#endif //INTERRUPT_H_

