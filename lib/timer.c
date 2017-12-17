
#include <embed/timer.h>


// https://electronics.stackexchange.com/questions/74840/use-avr-watchdog-like-normal-isr

ISR(TIMER1_COMPB_vect) {
    tick++;
}

ISR(WDT_vect) {
    tick++;

    // unset waiting flag to go back to sleep
    FLAG_VECT &= ~_BV(WAITING_INPUT);
    wdt_reset();
}


void init_timer1(uint8_t rate) {
    // setup timer interrupt with 1024 prescale
    TCCR1B |= _BV(CS10) | _BV(CS12);

    // setup clear on compare match
    TCCR1B |= _BV(WGM12);
    // set timer compare value
    OCR1A = rate;

    // enable timer interrupt
    TIMSK1 |= _BV(OCIE1B);
}

void init_wdt(uint8_t rate) {
    // set WDT to interrupt mode, not reset
    cli();
    // enable the WD change bit
    WDTCSR = (uint8_t)(_BV(WDCE) | _BV(WDE));
    // enable WDT interrupt and set to 8s
    // WDTCSR = (uint8_t)(_BV(WDIE) | WDTO_8S);
    // WDTCSR = (uint8_t)(_BV(WDIE) | _BV(WDP3) | _BV(WDP0));
    WDTCSR = (uint8_t)(_BV(WDIE) | rate);
    sei();
}

void init_timer(uint8_t rate, counter_t type) {
    tick = 0;

    if(type == TIMER1)
        init_timer1(rate);
    else if(type == WDT)
        init_wdt(rate);
}

