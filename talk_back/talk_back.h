
#ifndef TALK_BACK_H_
#define TALK_BACK_H_

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/wdt.h>

#include <embed/defs.h>
#include <embed/usart.h>
#include <embed/timer.h>
#include <embed/sleep.h>
#include <embed/interrupt.h>

#define START_CMD '>'
#define END_CMD '.'

#define EXIT "__exit__"

volatile extern uint8_t FLAG_VECT;

void toggle_tranceiver(toggle_t choice);
uint8_t get_cmd(char *cmd);
int talk_back(void);

#endif //TALK_BACK_H_


