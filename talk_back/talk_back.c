
#include "talk_back.h"

#include<util/delay.h>

// check flag to see if woken up
// https://arduino.stackexchange.com/questions/13167/put-atmega328-in-very-deep-sleep-and-listen-to-serial


void toggle_tranceiver(toggle_t choice) {
    _toggle(&UCSR0B, _BV(RXEN0) | _BV(TXEN0), choice);
}

int n = 0;
unsigned char test_usart_gets(char *cmd) {
    int len;
    n++;

    if(n == 1) {
        return strlcpy(cmd, "missed command.>start-", 23);
    } else if(n == 2) {
        return strlcpy(cmd, "end command.junk", 17);
    }

    return 0;
}

unsigned char get_cmd(char *cmd) {
    // get cmd (between START_CMD and END_CMD) from input string
    char *start_ptr = 0, *end_ptr = 0;
    unsigned char len, processed_len = 0;

    // loop until
    while(FLAG & _BV(WAITING_INPUT)) {
        PORTC ^= 4;

#ifdef TEST
        len = usart_gets(cmd + processed_len);
#else
        len = test_usart_gets(cmd + processed_len);
#endif // TEST

        int i;
        printf("-> %d cmd: ", n);
        for(i=0; i< len+processed_len; i++)
            printf("%c", cmd[i]);
        printf(" %d\n", len);

        start_ptr = strchr(cmd, START_CMD);

        // found start of command
        if(start_ptr) {
            // search for end of command
            end_ptr = strchr(start_ptr, END_CMD);
            if(end_ptr) {
                // ensure string is null terminated
                *(end_ptr + 1) = '\0';

                // copy command from start_ptr to end_ptr
                len = strlcpy(cmd, start_ptr + 1, end_ptr - start_ptr);
                assert(processed_len == strnlen(cmd, sizeof(cmd)));
                assert(processed_len == end_ptr - start_ptr + 1);
                printf("** start ptr-> end ptr: %d\n", end_ptr - start_ptr);

                return end_ptr - start_ptr - 1;

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
    char cmd[64];

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

