
#include "timer.h"


/*
ISR(TIMER1_COMPB_vect) {
    tick++;
}
*/

ISR(WDT_vect) {
    tick++;
}


void init_wdt(unsigned int rate) {

    // // set WDT to interrupt
    // WDTCSR |= _BV(WDIE)
    // WDTCSR &= ~_BV(WDE)

    // // setup timer interrupt with 1024 prescale
    // WDTCSR |= _BV(WDP3) | _BV(WDP0)

    wdt_enable(1);
}

void init_timer_1(unsigned int rate) {
    // setup pin interrupt
    //EIMSK |= _BV(INT0);
    // EICRA |= _BV(ISC00) | _BV(ISC01);

    // setup timer interrupt with 1024 prescale
    TCCR1B |= _BV(CS10) | _BV(CS12);

    // setup clear on compare match
    TCCR1B |= _BV(WGM12);
    // set timer compare value
    OCR1A = rate;

    // enable timer interrupt
    TIMSK1 |= _BV(OCIE1B);
}

void init_timer(unsigned int rate) {
    init_timer_1(rate);
}

