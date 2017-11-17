
#include "flash.h"

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

void setup_usart(void) {
    UBRR0H = (BAUDRATE >> 8);
    UBRR0L = BAUDRATE;
    UCSR0B |= _BV(TXEN0);
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
    setup_usart();
    setup_timer();

    FLAG_VECT = 0;
    sei();
}

void sleep_now(void) {
    set_sleep_mode(SLEEP_MODE_IDLE);

    sleep_enable();
    sleep_mode();

    // just woken up, yawn
    sleep_disable(); 
}

unsigned char rawKeyPressed() {
    return EICRA;
}

unsigned char debounceSwtich() {
    static uint16_t state = 0;
    state = (state<<1) | !rawKeyPressed() | 0xe000;
    if(state == 0xf000)
        return True;
    return False;
}

unsigned char usart_getc(void) {
    while(!(UCSR0A & _BV(UDRE0)))
        ;
    return UDR0; 
}

void usart_puts(const char *data) {
    usart_str = data;
    UCSR0B |= _BV(UDRIE0);
}

// disable INT0 interrput
//NO_ISR(INT0_vect) {
//    char int0[10];
//    usart_puts(PSTR("INT0_vect\t"));
//    utoa(EICRA, int0, 1);
//    usart_puts(int0);
//    usart_puts(PSTR("\n"));
//
//    // de-bounce switch
//    // http://www.ganssle.com/debouncing-pt2.htm
//
//    // set global variable that flash watches
//    if(debounceSwtich())
//        FLAG_VECT |= _BV(int_FLASH);
//}

ISR(TIMER1_COMPB_vect) {
    usart_puts(PSTR("TIMER1_COMPB_vect\n"));
    FLAG_VECT |= _BV(int_TIMER1_COMPB);
}

ISR(USART_UDRE_vect) {
    //FLAG_VECT |= _BV(int_NEXT_BYTE);
    UDR0 = 'a';//usart_str[0];
    UCSR0B &= ~_BV(UDRIE0);

    /*
    UDR0 = *usart_str++;

    if(*usart_str == 0) {
        //usart_str = 0;
        UCSR0B &= ~_BV(UDRIE0);
    }
    */
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

    while(True) {
        flag_vect = FLAG_VECT;
        pinb = PINB & _BV(PB1);

        // user pressed switch
        if(pinb && !count) {
            TCNT1 = 0;
            OCR1A = INT_RATE*2+1;
            portc = PORTC;
        }

        // check what interrupt was raised
        switch(flag_vect) {
            case _BV(int_TIMER1_COMPB):
            {
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

                break;
            }
            default:
            {
                // put mcu to sleep
                sleep_now();
                break;
            }
        }
        sleep_now();
    }

    return 0;
}

