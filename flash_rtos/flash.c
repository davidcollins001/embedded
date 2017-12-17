
#include "flash.h"


static void setup_port(void) {
    // setup pin direction
    DDRC = 0xFF;
    PORTC = 0;
    ADCSRA = 0;
}

static void init(void) {
    setup_port();
    init_rtos();

    // clear any existing interrupts
    EIFR = _BV(INTF0) | _BV(INTF1);

    FLAG_VECT = 0;
    sei();
}

void run1(void) {
    PORTC |= _BV(PC1);
}

void run2(void) {
    PORTC ^= _BV(PC2);
}

void runner(void) {

    add_task(run1, (uint16_t)8);
    add_task(run2, (uint16_t)4);

    while(true) {
        PORTC ^= _BV(PC3);
        sched();
    }
}

int main(void) {
    init();
    runner();
}

