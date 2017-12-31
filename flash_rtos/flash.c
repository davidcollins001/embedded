
#include "flash.h"


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

    // 1/8th of second
    init_rtos(3);

    // clear any existing interrupts
    EIFR = _BV(INTF0) | _BV(INTF1);

    FLAG_VECT = 0;
    sei();
}

static uint8_t flash_count = 0;

static uint8_t which(void) {
    // function to determine if increment or flash should be run
    uint8_t pinb = PINB & _BV(PB1);

    // switch has been pressed or in process of flashing
    return pinb || flash_count;
}

void flash_incr(void) {

    if(!which()) {
        usart_puts(PSTR("incr\n"));

        // change lights when timer interrupt happens
        if((PORTC == 0) || (PORTC >= 0x20))
            PORTC = 1;
        else
            PORTC = PORTC << 1;
    }
}

void flash(void) {
    uint8_t i;
    static uint8_t set = 0;

    if(which()) {
        usart_puts(PSTR("flash\n"));

        PORTC = 0;

        // set alternating leds to on
        for(i=set; i<5+set; i+=2)
            PORTC |= _BV(i);

        set ^= 1;

        // reset counter since number of flashes has expired
        if(++flash_count == 2*FLASHES)
            flash_count = 0;

    }
}

int main(void) {
    init();

    add_task(flash_incr, 8);
    add_task(flash, 4);

    while(true) {
        sched();
#ifdef TEST
        break;
#endif
    }
}

