
#include "interrupt.h"


ISR(PCINT2_vect) {
    FLAG |= _BV(WAITING_INPUT);
}

void init_interrupt(void) {
    // trigger interrupt on any logical change (rising or falling edge)
    PCICR |= _BV(PCIE2);
    PCICR |= _BV(PCIF2);
    PCMSK2 |= _BV(PCINT16);
}

void toggle_interrupt(toggle_t choice) {
    // _toggle(&PCICR, _BV(PCIE2), choice);
    if(choice == ON)
        PCICR |= _BV(PCIE2);
    else if(choice == OFF)
        PCICR &= ~_BV(PCIE2);
}

