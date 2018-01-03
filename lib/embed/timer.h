
#ifndef _TIMER_H_
#define _TIMER_H_

#include <avr/interrupt.h>
#include<avr/wdt.h>
#include<avr/io.h>

#include "defs.h"

typedef enum counter {TIMER1, WDT} counter_t;

uint8_t tick;

void init_timer(uint16_t rate, counter_t type);
void init_wdt(uint16_t rate);
void init_timer1(uint16_t rate);

#endif //_TIMER_H_

// input: abcde>abcd
// cmd:   abcde>abcd
// start_cmd:  |
