
#ifndef TALK_BACK_H_
#define TALK_BACK_H_

#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/wdt.h>

#include "defs.h"

#include "usart.h"
#include "timer.h"
#include "sleep.h"
#include "interrupt.h"

#define START_CMD '>'
#define END_CMD '.'

#define EXIT "exit"

extern unsigned char FLAG;

void toggle_tranceiver(toggle_t choice);
char get_cmd(char *cmd);
int talk_back(void);

#endif //TALK_BACK_H_


