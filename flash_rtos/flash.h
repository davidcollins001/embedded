
#ifndef __flash_h__
#define __flash_h__

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

#endif //__flash_h__

