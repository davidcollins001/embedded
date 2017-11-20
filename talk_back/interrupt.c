
#include "interrupt.h"


ISR(PCINT2_vect) {
    // switch off PCINT to use the pins for usart
    toggle_interrupt(OFF);
    // switch on usart
    toggle_tranceiver(ON);

    FLAG |= _BV(WAITING_INPUT);
    PORTC ^= 32;
}

void init_interrupt(void) {
    // trigger interrupt on any logical change (rising or falling edge)
    PCICR |= _BV(PCIE2);
    PCICR |= _BV(PCIF2);
    PCMSK2 |= _BV(PCINT16);
}

void toggle_interrupt(toggle_t choice) {
    _toggle(&PCICR, _BV(PCIE2), choice);
}

