
ctypedef signed char int8_t
ctypedef unsigned char uint8_t

cdef extern from "flash.h":
    void init()
    void runner()
    void run1()
    void run2()

cdef extern from "avr/io.h":
    uint8_t PORTC
    uint8_t PC1
    uint8_t PC2
    uint8_t PC3

