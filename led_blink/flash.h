
#ifndef _FLASH_H_
#define _FLASH_H_

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <avr/io.h>

#include <embed/defs.h>
#include <embed/rtos.h>

void init(void);
void runner(void);

void run1(void);
void run2(void);

#endif //_FLASH_H_

