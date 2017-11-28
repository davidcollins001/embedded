
#include "talk_back.h"

#include<util/delay.h>

// check flag to see if woken up
// https://arduino.stackexchange.com/questions/13167/put-atmega328-in-very-deep-sleep-and-listen-to-serial

static unsigned char partial_cmd_ptr = 0;

void toggle_tranceiver(toggle_t choice) {
    _toggle(&UCSR0B, _BV(RXEN0) | _BV(TXEN0), choice);
}

char *get_cmd(void) {
    // get cmd (between START_CMD and END_CMD) from input string
    char input[64], *data_ptr, *start_ptr = 0, *end_ptr = 0;
    unsigned char len, count = 0;

    // loop until
    while((len && *data_ptr != END_CMD) || (FLAG & _BV(WAITING_INPUT))) {
        PORTC ^= 4;

        len = usart_gets(input);
        data_ptr = input;

        start_ptr = strchr(data_ptr, START_CMD);
        // found start of command
        if(start_ptr) {

            end_ptr = strchr(start_ptr, END_CMD);
            // found end of command
            if(end_ptr) {
                // command is from start_ptr to end_ptr
                *(end_ptr + 1) = '\0';
                return start_cmd;

            }
        }
        else {
            // got partial command wait for rest
        }

        // use idle sleep - usart can wake
        // sleep_now(SLEEP_MODE_IDLE);
    }
    // didn't find the END_CMD char so reset
    partial_cmd_ptr = count;

    return -count;
}

static void prepare_sleep(void) {
    // disable watchdog before sleeping
    wdt_disable_int();

    // switch off usart
    toggle_tranceiver(OFF);
    // switch on PCINT to use the pins for usart
    toggle_interrupt(ON);

    PORTC = 255;
    _delay_ms(500);

    PORTC = 0;

    sleep_now(SLEEP_MODE_PWR_DOWN);

    // switch off PCINT to use the pins for usart
    toggle_interrupt(OFF);
    // switch on usart
    toggle_tranceiver(ON);

    // reset watchdog timer for interrupt
    // wdt_enable_int();
}

// TESTING:
//	1) setup wdt, sleep, wdt interrupt and flash light
//  2) as 1, setup wdt after sleep, usart interrupt
//	3) as 1 and 2, usart to wake, wdt to return to sleep

int talk_back(void) {
    unsigned char len = 0;
    char cmd[64], *cptr;

    while(true) {

        memset(cmd, 0, sizeof(cmd)/sizeof(cmd[0]));
        prepare_sleep();

        PORTC ^= 2;
        _delay_ms(500);

        len = get_cmd(cmd);

        if(len > 0) {
            PORTC ^= 8;

            // send input cmd back to usart
            // usart_puts(cmd);
            // cptr = cmd;
            // while(*cptr)
                // usart_putc(*cptr++);
            usart_putc(cmd[0]);

            while(!uart_tx_empty())
                ;

            // exit - needed to prevent tests spinning
            if(! strncmp(cmd, EXIT, 4))
                return 1;
        }
    }
    return 0;
}

