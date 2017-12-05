
ctypedef signed char int8_t
ctypedef unsigned char uint8_t

cdef extern from "talk_back.h":
    ctypedef enum toggle_t:
        ON
        OFF

    uint8_t get_cmd(char *cmd)
    void toggle_tranceiver(toggle_t choice)
    int talk_back()
    uint8_t FLAG


cdef extern from "interrupt.h":
    void isr_PCINT2_vect()


cdef extern from "avr/io.h":
    uint8_t UCSR0B
    uint8_t RXEN0
    uint8_t TXEN0
    uint8_t UDRE0
    uint8_t UCSR0A

