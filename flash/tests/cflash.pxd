
ctypedef signed char int8_t
ctypedef unsigned char uint8_t

cdef extern from "flash.h":
    void flash(unsigned char set);
    void flash_incr();


cdef extern from "embed/interrupt.h":
    isr_TIMER1_COMPB_vect();


cdef extern from "avr/io.h":
    uint8_t UCSR0B
    uint8_t RXEN0
    uint8_t TXEN0
    uint8_t UDRE0
    uint8_t UCSR0A

