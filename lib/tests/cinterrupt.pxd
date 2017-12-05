
ctypedef unsigned char uint8_t

cdef extern from "interrupt.h":
    ctypedef enum toggle_t:
        ON
        OFF
    void toggle_interrupt(toggle_t choice)


cdef extern from "avr/io.h":
    uint8_t PCICR
    uint8_t PCIE2

