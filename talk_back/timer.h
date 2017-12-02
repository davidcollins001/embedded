
#ifndef TIMER_H_
#define TIMER_H_

#include <avr/interrupt.h>
#include<avr/wdt.h>
#include<avr/io.h>

#include "defs.h"

uint8_t tick;

void init_timer(int rate);
void wdt_enable_int(void);
void wdt_disable_int(void);
void init_timer_1(uint8_t rate);

#endif //TIMER_H_

// input: abcde>abcd
// cmd:   abcde>abcd
// start_cmd:  |
