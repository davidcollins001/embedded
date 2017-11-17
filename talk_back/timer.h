
#ifndef TIMER_H_
#define TIMER_H_

#include <avr/interrupt.h>
#include "defs.h"
#include<avr/wdt.h>

void init_timer(unsigned int rate);

unsigned char tick;

#endif //TIMER_H_

