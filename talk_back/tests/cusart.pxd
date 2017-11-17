
cdef extern from "../usart.h":
    void usart_puts(const char *data)
    void usart_gets(char *data)

    void isr_USART_UDRE_vect()
    void isr_USART_RX_vect()

    ctypedef struct buffer_t:
        char data[64]
        unsigned char head, tail

    buffer_t _buffer_debug(char buf, char debug)


cdef extern from "lib/io.h":
    unsigned char UBRR0H
    unsigned char UBRR0L
    unsigned char RXCIE0
    unsigned char UCSR0B
    unsigned char UDRIE0
    unsigned char RXC0
    unsigned char UCSR0A
    unsigned char UDRE0
    unsigned char UDR0

