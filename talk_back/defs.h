
#ifndef DEFS_H_
#define DEFS_H_

#include<stdbool.h>
#include <inttypes.h>

#define INT_RATE 8199
#define TX_IN_PROGRESS 0x1
#define WAITING_INPUT 0x1

typedef enum toggle {ON, OFF} toggle_t;
extern unsigned char FLAG;

void _toggle(volatile uint8_t *reg, uint8_t mask, toggle_t choice);

#endif //DEFS_H_

