
#include "timer.h"


// https://electronics.stackexchange.com/questions/74840/use-avr-watchdog-like-normal-isr

/*
ISR(TIMER1_COMPB_vect) {
    tick++;
}
*/

ISR(WDT_vect) {
    // unset waiting flag to go back to sleep
    FLAG &= ~_BV(WAITING_INPUT);
    PORTC ^= 16;
}

void wdt_disable_int(void) {
    // Clear the WDT reset flag
    MCUSR &= ~_BV(WDRF);
    // Enable the WD Change Bit
    WDTCSR |= (_BV(WDCE) | _BV(WDE));
    // Disable the WDT
    WDTCSR = 0x00;
}


void wdt_enable_int(void) {
    // set WDT to interrupt mode, not reset
    cli();
    // enable the WD change bit
    WDTCSR = (unsigned char)(_BV(WDCE) | _BV(WDE));
    // enable WDT interrupt and set to 8s
    //WDTCSR = (unsigned char)(_BV(WDIE) | WDTO_8S);
    WDTCSR = (unsigned char)(_BV(WDIE) | _BV(WDP3) | _BV(WDP0));
    sei();
}

void init_timer_1(unsigned char rate) {
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

void init_timer(int rate) {
    tick = 0;

    // init_timer_1(rate);
}

