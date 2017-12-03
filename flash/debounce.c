
#include<stdbool.h>

#include<avr/io.h>

unsigned char rawKeyPressed() {
    return EICRA;
}

unsigned char debounceSwtich() {
    static uint16_t state = 0;
    state = (state<<1) | !rawKeyPressed() | 0xe000;
    if(state == 0xf000)
        return true;
    return false;
}


// disable INT0 interrput
//NO_ISR(INT0_vect) {
//    char int0[10];
//    usart_puts(PSTR("INT0_vect\t"));
//    utoa(EICRA, int0, 1);
//    usart_puts(int0);
//    usart_puts(PSTR("\n"));
//
//    // de-bounce switch
//    // http://www.ganssle.com/debouncing-pt2.htm
//
//    // set global variable that flash watches
//    if(debounceSwtich())
//        FLAG_VECT |= _BV(int_FLASH);
//}

