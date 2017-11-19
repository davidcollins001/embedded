
cdef extern from "../interrupt.h":
    ctypedef enum toggle_t:
        ON
        OFF
    void toggle_interrupt(toggle_t choice)


cdef extern from "lib/avr/io.h":
    unsigned char PCICR
    unsigned char PCIE2

