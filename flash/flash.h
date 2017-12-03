
#ifndef __flash_h__
#define __flash_h__

#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

#define FLASHES 5
#define BAUD  9600
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)

#define int_FLASH 0x1
#define int_TIMER1_COMPB 0x2
#define int_NEXT_BYTE 0X3

// TODO: make usart interrupt

// flag to indicate interrupt has ocurred
volatile unsigned char FLAG_VECT = 0;

void setup_port(void);
void setup_timer(void);

void init(void);

void flash(unsigned char set);
void flash_incr(void);

#endif //__flash_h__

