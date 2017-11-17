
#include "main.h"
#include "usart.h"
#include "interrupt.h"

#include<util/delay.h>
#include<stdlib.h>

unsigned char FLAG = 0;
#define WAITING_INPUT 0x1

void init(void) {
    // setup pin direction
    DDRC = 0xFF;
    PORTC = 0;
    ADCSRA = 0;

    init_usart();
    init_timer(INT_RATE);
    init_pcint2();

    // clear any existing interrupts
    EIFR = _BV(INTF0) | _BV(INTF1);

    sei();
}

// wake up on rx
//https://arduino.stackexchange.com/questions/13167/put-atmega328-in-very-deep-sleep-and-listen-to-serial

typedef enum xcvr {XCVR_ON, XCVR_OFF} xcvr_t;

void toggle_tranceiver(xcvr_t choice) {
    if(choice == XCVR_ON) {
        UCSR0B |= _BV(RXEN0) | _BV(TXEN0);
        PCICR &= ~_BV(PCIE2);
    }
    else if(choice == XCVR_OFF) {
        UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
        PCICR &= _BV(PCIE2);
    }
}

int main(void) {
    char input[64], cmd[64];

    init();
    usart_puts_P(PSTR("init...\n"));
    toggle_tranceiver(XCVR_OFF);

    while(true) {
        toggle_tranceiver(XCVR_OFF);
        sleep_now(SLEEP_MODE_PWR_DOWN);
        PORTC ^= 4;
        toggle_tranceiver(XCVR_ON);
        usart_gets(input);
        while(*input++ != '>') {

        }
        break;
    }


    /*
    while(true) {
        usart_puts_P(PSTR("ready?"));

        usart_gets(str);
        if((str[0] == 'y') || (str[0] == 'Y')) {
            usart_puts_P(PSTR("You are ready\n"));
            FLAG &= ~WAITING_INPUT;
            break;
        }

        while(!uart_tx_complete())
            ;

        // sleep_now(SLEEP_MODE_PWR_DOWN);
        sleep_now(SLEEP_MODE_IDLE);
    }

    while(true) {
        PORTC ^= 4;

        toggle_tranceiver(XCVR_ON);

        usart_puts_P(PSTR("enter string: "));

        if(false) { //FLAG & WAITING_INPUT) {
            usart_puts_P(PSTR("\nentered: \n"));
            usart_gets(str);
            usart_puts(str);
            usart_puts_P(PSTR("\n"));
            FLAG &= ~WAITING_INPUT;
        }

        while(!uart_tx_complete())
            ;

        toggle_tranceiver(XCVR_OFF);

        // sleep and wait for input
        sleep_now(SLEEP_MODE_PWR_DOWN);
        //sleep_now(SLEEP_MODE_IDLE);
    }
    */

    return 0;
}

