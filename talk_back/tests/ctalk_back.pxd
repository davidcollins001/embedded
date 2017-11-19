
cdef extern from "../talk_back.h":
    ctypedef enum toggle_t:
        ON
        OFF
    int get_cmd(char *cmd)
    void toggle_tranceiver(toggle_t choice)
    int talk_back()


cdef extern from "lib/avr/io.h":
    unsigned char UCSR0B
    unsigned char RXEN0
    unsigned char TXEN0


cdef extern from "../interrupt.h":
    void isr_PCINT2_vect();

