
#include <avr/interrupt.h>

#include "talk_back.h"


static void init(void) {
    // setup pin direction
    DDRC = 0xFF;
    PORTC = 0;
    ADCSRA = 0;

    init_usart();
    init_timer(INT_RATE);
    init_interrupt();

    // clear any existing interrupts
    EIFR = _BV(INTF0) | _BV(INTF1);

    sei();
}

int main(void) {
    init();
    PORTC |= 1;

    talk_back();

    return 0;
}

