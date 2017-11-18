
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#include <avr/pgmspace.h>
#include <avr/io.h>

#include "usart.h"
#include "timer.h"
#include "sleep.h"
#include "interrupt.h"
#include "talk_back.h"

#include "defs.h"

#include<util/delay.h>


static void init(void) {
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

static void toggle_tranceiver(xcvr_t choice) {
    if(choice == XCVR_ON) {
        UCSR0B |= _BV(RXEN0) | _BV(TXEN0);
        PCICR &= ~_BV(PCIE2);
    }
    else if(choice == XCVR_OFF) {
        UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
        PCICR |= _BV(PCIE2);
    }
}

int get_cmd(char *data, char *cmd) {
    char *data_ptr = data, *cmd_ptr = cmd;
    unsigned char count = 0;

    while(*data_ptr) {

        // end of input found
        if(count && (*data_ptr == '.'))
            return count;

        // start of input found
        if((*data_ptr == '>') || count) {
            // move past start pointer
            if(!count)
                data_ptr++;
            // copy cmd from data to cmd buffer
            *cmd_ptr++ = *data_ptr;
            count++;
        }
        data_ptr++;
    }
    return count;
}

int talk_back(void) {
    int len = 0;
    char input[64], cmd[64];

    init();
    toggle_tranceiver(XCVR_ON);
    usart_puts_P(PSTR("init...\n"));
    PORTC |= 1;

    while(true) {
        PORTC ^= 2;
        toggle_tranceiver(XCVR_OFF);
        sleep_now(SLEEP_MODE_PWR_DOWN);
        toggle_tranceiver(XCVR_ON);

        // check flag to see if woken up
        // wait to see input
        // https://arduino.stackexchange.com/questions/13167/put-atmega328-in-very-deep-sleep-and-listen-to-serial

        while(rx_interrupt) {
            len = usart_gets(input);
            // set timer for N secs
            // wait for input or
            // set rx_interrupt = False after timeout
            //

            if(len) {
                PORTC ^= 4;
                // get cmd (between > and .) from input string
                len = get_cmd(input, cmd);

                // send input cmd back to usart
                usart_puts(cmd);

                // exit - needed to prevent tests spinning
                if(! strncmp(cmd, EXIT, 4))
                {
                    PORTC ^= 8;
                    return 0;
                }
                break;
            }
        }
    }
    return 1;


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

}

