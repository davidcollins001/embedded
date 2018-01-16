
from libc.stdint cimport uint8_t, uint16_t

cdef extern from "primes.h":
    bint is_prime(uint16_t number)
    void computePrimes(uint16_t id_)
    void printAt(uint8_t id_, uint16_t number)
    int runner()


cdef extern from "embed/usart.h":
    void isr_USART_UDRE_vect()


cdef extern from "avr/io.h":
    uint8_t UCSR0B
    uint8_t UDRIE0
    uint8_t UDR0

