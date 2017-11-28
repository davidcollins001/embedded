
#include "timer.h"


/*
ISR(TIMER1_COMPB_vect) {
    tick++;
}
*/

ISR(WDT_vect) {
    // unset waiting flag to go back to sleep
    FLAG &= ~_BV(WAITING_INPUT);
}

void wdt_enable_int(void) {
    // set WDT to interrupt mode, not reset

	// Watchdog Timer initialization
	// Watchdog Timer Prescaler: OSC/1024k
	// Watchdog timeout action: Interrupt
#pragma optsize-
	// enter watchdog config mode
	WDTCSR = (_BV(WDCE) | _BV(WDE));
	// set interrupt mode with 1024 prescalar (8s)
	WDTCSR = ((0<<WDE) | (0<<WDE) | _BV(WDP3) | _BV(WDP0));
	// TODO: what is value of WD_8S compared to WDP3|WDP0
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif
}

void wdt_disable_int(void) {
    // set WDT to stopped mode
    WDTCSR = ~_BV(WDIE) & ~_BV(WDE);
}

void init_wdt(unsigned char rate) {
    // reset any watchdog resets
    MCUSR = 0;

    // set WDT to interrupt mode, not reset
    wdt_enable_int();

    // setup timer interrupt with 1024 prescale - 8s
    WDTCSR |= _BV(WDP3) | _BV(WDP0);
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

    init_timer_1(rate);
    // init_wdt(rate);
}

