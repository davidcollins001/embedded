
#include "talk_back.h"

#include<util/delay.h>

static unsigned char partial_cmd_ptr = 0;

void toggle_tranceiver(toggle_t choice) {
    _toggle(&UCSR0B, _BV(RXEN0) | _BV(TXEN0), choice);
}

char get_cmd(char *cmd) {
    // get cmd (between START_CMD and END_CMD) from input string
    char input[64], *data_ptr, *cmd_ptr = cmd;
    unsigned char len, count = 0;

    cmd_ptr = cmd + partial_cmd_ptr;

    len = usart_gets(input);
    data_ptr = input;

    while(len && *data_ptr) {

        // start of input found
        if((*data_ptr == START_CMD) || count || partial_cmd_ptr) {
            // move past start pointer
            if(!count && !partial_cmd_ptr)
                data_ptr++;

            // end of input found
            if(*data_ptr == END_CMD) {
                count += partial_cmd_ptr;
                partial_cmd_ptr = 0;
                return count;
            }

            // copy cmd from data to cmd buffer
            *cmd_ptr++ = *data_ptr;

            count++;
        }
        data_ptr++;
    }
    // didn't find the END_CMD char so reset
    partial_cmd_ptr = count;

    return -count;
}

static void prepare_sleep(void) {
    // switch off watchdog timer
    wdt_disable_int();

    // switch off usart
    toggle_tranceiver(OFF);
    // switch on PCINT to use the pins for usart
    toggle_interrupt(ON);

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
    char cmd[64];

    while(true) {
        prepare_sleep();

        PORTC ^= 2;

        // check flag to see if woken up
        // https://arduino.stackexchange.com/questions/13167/put-atmega328-in-very-deep-sleep-and-listen-to-serial

        while(FLAG & _BV(WAITING_INPUT)) {
            PORTC ^= 4;

            len = get_cmd(cmd);

            // use idle sleep - usart can wake
            // sleep_now(SLEEP_MODE_IDLE);

            if(len) {
                PORTC ^= 8;

                // send input cmd back to usart
                usart_puts(cmd);
                while(uart_tx_complete())
                    ;

                // exit - needed to prevent tests spinning
                if(! strncmp(cmd, EXIT, 4))
                {
                    PORTC ^= 16;
                    return 0;
                }
                // return to outer loop
                break;
            }
        }
    }
    return 1;
}

