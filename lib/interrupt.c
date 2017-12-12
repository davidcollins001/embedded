
#include <embed/interrupt.h>


ISR(PCINT2_vect) {
    FLAG_VECT |= _BV(WAITING_INPUT);
}

ISR(TIMER1_COMPB_vect) {
    FLAG_VECT |= _BV(int_TIMER1_COMPB);
}

void init_interrupt(uint8_t type) {
    if(type == 0) {
        // setup pin interrupt
        EIMSK |= _BV(INT0);
        EICRA |= _BV(ISC00) | _BV(ISC01);
    } else if(type == 1) {
        // trigger interrupt on any logical change (rising or falling edge)
        PCICR |= _BV(PCIE2);
        PCICR |= _BV(PCIF2);
        PCMSK2 |= _BV(PCINT16);
    }
}

void toggle_interrupt(toggle_t choice) {
    // _toggle(&PCICR, _BV(PCIE2), choice);
    if(choice == ON)
        PCICR |= _BV(PCIE2);
    else if(choice == OFF)
        PCICR &= ~_BV(PCIE2);
}

