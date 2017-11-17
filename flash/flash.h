
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

#define F_CPU 14745600
#include <util/delay.h>
 
#define True 1
#define False 0

#define FLASHES 5
#define BAUD  9600
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)

#define int_FLASH 0x1
#define int_TIMER1_COMPB 0x2
#define int_NEXT_BYTE 0X3
#define INT_RATE 4099

// TODO: make usart interrupt

// flag to indicate interrupt has ocurred
volatile unsigned char FLAG_VECT = 0;

void setup_port(void);

void setup_usart(void);

void setup_timer(void);

void init(void);

void sleep_now(void);

unsigned char rawKeyPressed();

unsigned char debounceSwtich();

unsigned char usart_getc(void);

void usart_puts(const char *data);

void flash(unsigned char set);

void flash_incr(void);


int main(void);

#endif //__flash_h__

