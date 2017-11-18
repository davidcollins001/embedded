
#include "interrupt.h"

#define WAITING_INPUT 0x1

void init_pcint2(void) {
    // trigger interrupt on any logical change (rising or falling edge)
    PCICR |= _BV(PCIE2);
    PCICR |= _BV(PCIF2);
    PCMSK2 |= _BV(PCINT16);
}

ISR(PCINT2_vect) {
    // used to wake up mcu
    // determine which pin interrupt was on if more than one
    // PORTC ^= 1;
}

