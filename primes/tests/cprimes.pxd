
from stdint cimport uint16_t, uint16_t

cdef extern from "primes.h":
    bint is_prime(uint16_t i)
    void computePrimes(uint8_t id)
    void printAt(uint8_t id, uint16_t num)


cdef extern from "embed/usart.h":
    void usart_puts(const char *data)

