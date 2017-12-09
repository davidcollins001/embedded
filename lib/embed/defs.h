
#ifndef DEFS_H_
#define DEFS_H_

#include<stdbool.h>
#include <inttypes.h>

#define INT_RATE 8199
#define TX_IN_PROGRESS 0x1
#define WAITING_INPUT 0x1

#if defined(_WIN32)
#define inline __inline
#endif

typedef enum toggle {ON, OFF} toggle_t;
extern uint8_t FLAG;

// generic function to toggle a register
inline void _toggle(volatile uint8_t *reg, uint8_t mask, toggle_t choice) {
    if(choice == ON)
        *reg |= mask;
    else if(choice == OFF)
        *reg &= ~mask;
}

#endif //DEFS_H_
