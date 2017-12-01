
#include "talk_back.h"

#include<util/delay.h>

// check flag to see if woken up
// https://arduino.stackexchange.com/questions/13167/put-atmega328-in-very-deep-sleep-and-listen-to-serial


// TODO: turn this into a cython function
unsigned char test_usart_gets(char *cmd) {
    char len, *msg, SPLIT_CHAR = '|';
    static char n = 0, *msg1, *msg2, reset = true;

    // both strings have been written at once, with a separator the string
    // will be consumed in two goes to test continuation in get_cmd()
    if(n == 0) {
        len = usart_gets(cmd);
        msg1 = cmd;
        msg2 = strchr(cmd, SPLIT_CHAR);
        if(msg2) {
            *msg2 = '\0';
            *msg2++;
            // expecting a split message so don't reset counter
            reset = false;
        }
    }

	n++;

    if(n == 2) {
        // following doesn't seem to work
        // msg = (n == 1) ? msg1 : msg 2;
        if(n == 1)
            msg = msg1;
        else {
            msg = msg2;
        }
    } else
        msg = msg1;

    if(reset == true) {
        n = 0;
        msg1 = msg2 = NULL;
    }

#ifdef _WIN32
	strncpy(cmd, msg, strlen(msg)+1);
	return strlen(msg);
#else
	return (unsigned char)strlcpy(cmd, msg, strlen(msg)+1);
#endif
}


void toggle_tranceiver(toggle_t choice) {
    _toggle(&UCSR0B, _BV(RXEN0) | _BV(TXEN0), choice);
}

unsigned char get_cmd(char *cmd) {
    // get cmd (between START_CMD and END_CMD) from input string
    char *start_ptr = 0, *end_ptr = 0;
    unsigned char len, processed_len = 0;

    // loop until
    while(FLAG & _BV(WAITING_INPUT)) {
        PORTC ^= 4;

#ifndef TEST
        len = usart_gets(cmd + processed_len);
#else
        len = test_usart_gets(cmd + processed_len);
#endif // TEST

        // search for start of command
        start_ptr = strchr(cmd, START_CMD);
        if(start_ptr) {
            // search for end of command
            end_ptr = strchr(start_ptr, END_CMD);
            if(end_ptr) {
                // copy command from start_ptr to end_ptr
#ifdef _WIN32
                len = strncpy(cmd, start_ptr + 1, end_ptr - start_ptr );
#else
                len = strlcpy(cmd, start_ptr + 1, end_ptr - start_ptr);
#endif
                // ensure command string is null terminated
                *(cmd + (end_ptr - start_ptr) - 1) = '\0';

                assert(processed_len == strnlen(cmd, sizeof(cmd)));
                assert(processed_len == end_ptr - start_ptr + 1);

                return (unsigned char)((end_ptr - start_ptr) - 1);

            } else {
                // keep track of how much command so far
                processed_len += len;
            }
        }
        // use idle sleep - usart can wake
        // sleep_now(SLEEP_MODE_IDLE);
    }
    return 0;
}

static void prepare_sleep(void) {
    // disable watchdog before sleeping
    wdt_disable_int();

    // switch off usart
    toggle_tranceiver(OFF);
    // switch on PCINT to use the pins for usart
    toggle_interrupt(ON);

    PORTC = 255;
    _delay_ms((char)500);

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
        printf("cmd: \n" );

        memset(cmd, 0, sizeof(cmd)/sizeof(cmd[0]));
        prepare_sleep();

        PORTC ^= 2;
        _delay_ms((char)500);

        len = get_cmd(cmd);

        if(len > 0) {
            PORTC ^= 8;

            // send input cmd back to usart
            // usart_puts(cmd);
            cptr = cmd;
            while(*cptr)
                usart_putc(*cptr++);

        printf(": \n" );
            while(!uart_tx_empty())
                ;

            // exit - needed to prevent tests spinning
            if(! strncmp(cmd, EXIT, 4))
                return 1;
        }
    }
    return 0;
}

