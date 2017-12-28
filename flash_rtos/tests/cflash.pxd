
ctypedef signed char int8_t
ctypedef unsigned char uint8_t

cdef extern from "flash.h":
    void flash()
    void flash_incr()


cdef extern from "avr/io.h":
    uint8_t PINB
    uint8_t PB1
    uint8_t PORTC

