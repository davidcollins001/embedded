
#include "flash.h"
#include "../talk_back/usart.h"
#include "../talk_back/sleep.h"

const volatile char* usart_str;

void setup_port(void) {
    // setup pin direction
    DDRC = 0xFF;
    PORTC = 0;
    ADCSRA = 0;

    // set portb2 as input
    DDRB &= ~_BV(PB1);
    PINB = 0;
}

void setup_timer(void) {
    // setup pin interrupt
    //EIMSK |= _BV(INT0);
    EICRA |= _BV(ISC00) | _BV(ISC01);

    // setup timer interrupt with 1024 prescale
    TCCR1B |= _BV(CS10) | _BV(CS12);

    // setup clear on compare match
    TCCR1B |= _BV(WGM12);
    // set timer compare value
    OCR1A = INT_RATE;

    // enable timer interrupt
    TIMSK1 |= _BV(OCIE1B);

    // clear any existing interrupts
    EIFR = _BV(INTF0) | _BV(INTF1);
}

void init(void) {
    setup_port();
    init_usart(false);
    setup_timer();

    FLAG_VECT = 0;
    sei();
}

ISR(TIMER1_COMPB_vect) {
    usart_puts(PSTR("TIMER1_COMPB_vect\n"));
    FLAG_VECT |= _BV(int_TIMER1_COMPB);
}

void flash(unsigned char set) {
    unsigned char i;
    usart_puts(PSTR("flash\n"));

    PORTC = 0;

    for(i=set; i<5+set; i+=2)
        PORTC |= _BV(i);
}

void flash_incr(void) {
    usart_puts(PSTR("incr\n"));

    // change lights when timer interrupt happens
    if((PORTC == 0) || (PORTC >= 0x20))
        PORTC = 1;
    else
        PORTC = PORTC << 1;
}


int main(void) {
    unsigned char count = 0;
    unsigned char flag_vect;
    unsigned char set = 0;
    unsigned char pinb = 0, portc = 0;

    init();

    while(true) {
        flag_vect = FLAG_VECT;
        pinb = PINB & _BV(PB1);

        // user pressed switch
        if(pinb && !count) {
            TCNT1 = 0;
            OCR1A = INT_RATE*2+1;
            portc = PORTC;
        }

        // check what interrupt was raised
        if(flag_vect & _BV(int_TIMER1_COMPB)) {
                // reset timer if that was trigger
                FLAG_VECT &= ~_BV(int_TIMER1_COMPB);

                // run code associated with interrupt
                if(pinb || count) {
                    flash(set);

                    // reset interrupt/port after desired flashes
                    if(count++ == 2*FLASHES) {
                        // double rate/half delay
                        OCR1A = INT_RATE;
                        count = 0;
                        PORTC = portc;
                    }
                    set ^= 1;
                }
                else
                    flash_incr();
        }
        // put mcu to sleep
        sleep_now(SLEEP_MODE_IDLE);
    }

    return 0;
}

