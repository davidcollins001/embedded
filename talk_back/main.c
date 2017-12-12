
#include <avr/interrupt.h>

#include <embed/usart.h>
#include <embed/timer.h>
#include <embed/interrupt.h>

#include "talk_back.h"


static void init(void) {
    // setup pin direction
    DDRC = 0xFF;
    PORTC = 0;
    ADCSRA = 0;

    init_usart(true);
    init_timer(INT_RATE);
    init_interrupt((uint8_t)1);

    // clear any existing interrupts
    EIFR = _BV(INTF0) | _BV(INTF1);

    sei();
}

int main(void) {
    init();

    talk_back();

    return 0;
}

