
#include "flash.h"

const volatile char* usart_str;

static void setup_port(void) {
    // setup pin direction
    DDRC = 0xFF;
    PORTC = 0;
    ADCSRA = 0;

    // set portb2 as input
    DDRB &= ~_BV(PB1);
    PINB = 0;
}

static void init(void) {
    setup_port();
    init_usart(false);
    init_interrupt(0);
    init_timer(RATE);

    // clear any existing interrupts
    EIFR = _BV(INTF0) | _BV(INTF1);

    FLAG_VECT = 0;
    sei();
}

void flash(uint8_t set) {
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


void runner(void) {
    uint8_t count = 0, flag_vect, set = 0, pinb = 0, portc = 0;

    init();

    while(true) {
        flag_vect = FLAG_VECT;
        pinb = PINB & _BV(PB1);

        // user pressed switch
        if(pinb && !count) {
            TCNT1 = (uint8_t)0;
            OCR1A = (uint8_t)INT_RATE*2+1;
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
                        OCR1A = (uint8_t)INT_RATE;
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
}

int main(void) {
    runner();
}

