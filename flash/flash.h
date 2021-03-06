
#ifndef _FLASH_H_
#define _FLASH_H_

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <avr/io.h>

#include <embed/usart.h>
#include <embed/sleep.h>
#include <embed/timer.h>
#include <embed/interrupt.h>

#include <embed/defs.h>

#define FLASHES 5
#define BAUD  9600
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)

#define int_FLASH 0x1
#define int_NEXT_BYTE 0X3

#define RATE 4099

// flag to indicate interrupt has ocurred
// volatile uint8_t FLAG_VECT = 0;

void flash(uint8_t set);
void flash_incr(void);
void runner(void);

#endif //_FLASH_H_

