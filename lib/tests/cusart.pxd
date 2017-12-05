
ctypedef unsigned char uint8_t

cdef extern from "usart.h":
    void usart_puts(const char *data)
    int usart_gets(char *data)

    void isr_USART_UDRE_vect()
    void isr_USART_RX_vect()

    ctypedef struct buffer_t:
        char data[64]
        uint8_t head, tail

    buffer_t _buffer_debug(char buf, char debug)


cdef extern from "avr/io.h":
    uint8_t UBRR0H
    uint8_t UBRR0L
    uint8_t RXCIE0
    uint8_t UCSR0B
    uint8_t UDRIE0
    uint8_t RXC0
    uint8_t UCSR0A
    uint8_t UDRE0
    uint8_t UDR0

