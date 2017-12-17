
ctypedef signed char int8_t
ctypedef unsigned char uint8_t

cdef extern from "flash.h":
    void flash(uint8_t set)
    void flash_incr()
    void runner()


cdef extern from "embed/timer.h":
    uint8_t int_TIMER1_COMPB


cdef extern from "avr/io.h":
    uint8_t PINB
    uint8_t PB1
    uint8_t PORTC
    uint8_t OCR1A
    uint8_t FLAG_VECT

