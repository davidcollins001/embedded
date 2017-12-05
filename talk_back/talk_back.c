
#include "talk_back.h"

// check flag to see if woken up
// https://arduino.stackexchange.com/questions/13167/put-atmega328-in-very-deep-sleep-and-listen-to-serial


// TODO: turn this into a cython function
int8_t test_usart_gets(char *cmd) {
    char *msg, SPLIT_CHAR = '|';
    uint8_t reset = true;
    static char *msg2;
    static uint8_t n = 0;

    msg = cmd;

    // both strings have been written at once, with a separator the string
    // will be consumed in two goes to test continuation in get_cmd()
    if(n == 0) {
        usart_gets(cmd);
        msg2 = strchr(cmd, SPLIT_CHAR);
        if(msg2) {
            *msg2 = '\0';
            msg2++;
            // expecting a split message so don't reset counter
            reset = false;
        }
    } else if(n == 1)
        // second time here, simulate second string being received
        msg = msg2;

    // should have had full command reset markers for next command
    if(reset == true) {
        n = 0;
        msg2 = NULL;
    } else
        n++;

#ifdef _WIN32
	strncpy(cmd, msg, strlen(msg)+1);
	return (int8_t)strlen(msg);
#else
	return (int8_t)strlcpy(cmd, msg, strlen(msg)+1);
#endif
}


void toggle_tranceiver(toggle_t choice) {
    _toggle(&UCSR0B, _BV(RXEN0) | _BV(TXEN0), choice);
}

uint8_t get_cmd(char *cmd) {
    // get cmd (between START_CMD and END_CMD) from input string
    char *start_ptr = 0, *end_ptr = 0;
    uint8_t len, processed_len = 0;

    // loop until watchdog expires
    while(FLAG & _BV(WAITING_INPUT)) {

#ifndef TEST
        len = usart_gets(cmd + processed_len);
#else
        len = test_usart_gets(cmd + processed_len);
#endif // TEST

        if(len) {
            // search for start of command
            start_ptr = strchr(cmd, START_CMD);
            if(start_ptr) {
                // search for end of command
                end_ptr = strchr(start_ptr, END_CMD);
                if(end_ptr) {
                    // copy command from start_ptr to end_ptr
#ifdef _WIN32
                    strncpy(cmd, start_ptr + 1, end_ptr - start_ptr - 1);
                    // ensure command string is null terminated
                    *(cmd + (end_ptr - start_ptr) - 1) = '\0';
                    len = strlen(cmd);
#else
                    len = strlcpy(cmd, start_ptr + 1, end_ptr - start_ptr + 1);
#endif
                    // assert((end_ptr - start_ptr) - 1 == strnlen(cmd, len));

                    return ((end_ptr - start_ptr) - 1);

                } else {
                    // keep track of how much command so far
                    processed_len += len;
                }
            }
            // use idle sleep - usart can wake
            // sleep_now(SLEEP_MODE_IDLE);
        }
    }
    return 0;
}

static void prepare_sleep(void) {
    // disable watchdog before sleeping
    wdt_disable();

    // switch off usart
    toggle_tranceiver(OFF);
    // switch on PCINT to use the pins for usart
    toggle_interrupt(ON);

    sleep_now(SLEEP_MODE_PWR_DOWN);

    // switch off PCINT to use the pins for usart
    toggle_interrupt(OFF);
    // switch on usart
    toggle_tranceiver(ON);

    // reset watchdog timer for interrupt
    wdt_enable_int();
}

// TESTING:
//	1) setup wdt, sleep, wdt interrupt and flash light
//  2) as 1, setup wdt after sleep, usart interrupt
//	3) as 1 and 2, usart to wake, wdt to return to sleep

int talk_back(void) {
    uint8_t len = 0;
    char cmd[64];

    while(true) {

        memset(cmd, 0, sizeof(cmd));
        prepare_sleep();

        len = get_cmd(cmd);

        if(len > 0) {
            // send input cmd back to usart
            usart_puts("\n>>> ");
            usart_puts(cmd);
            usart_puts("\n");

#ifndef TEST
            while(!uart_tx_empty())
                ;
#else
            // exit - needed to prevent tests spinning
            if(! strncmp(cmd, EXIT, 4))
                return 1;
#endif
        }
    }
    return 0;
}

