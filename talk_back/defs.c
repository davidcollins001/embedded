
#include "defs.h"

unsigned char FLAG = 0;

// generic function to toggle a register
void _toggle(volatile uint8_t *reg, uint8_t mask, toggle_t choice) {
    if(choice == ON)
        *reg |= mask;
    else if(choice == OFF)
        *reg &= ~mask;
}

