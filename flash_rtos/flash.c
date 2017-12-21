
#include "flash.h"


static void setup_port(void) {
    // setup pin direction
    DDRC = 0xFF;
    PORTC = 0;
    ADCSRA = 0;
}

void init(void) {
    setup_port();
    init_rtos();

    add_task(run1, 8);
    add_task(run2, 4);

    // clear any existing interrupts
    EIFR = _BV(INTF0) | _BV(INTF1);

    sei();
}

void run1(void) {
    PORTC ^= _BV(PC1);
}

void run2(void) {
    PORTC ^= _BV(PC2);
}

void runner(void) {

    while(true) {
        PORTC ^= _BV(PC3);
        sched();

#ifdef TEST
        // allow tests to run code
        break;
#endif
    }
}

int main(void) {
    init();

    runner();
}

