
//#define SERIAL_USART

#include "usart.h"

static inline void enable_receiving(void);

void init_usart(void) {
    UBRR0H = (BAUDRATE >> 8);
    UBRR0L = BAUDRATE;
    UCSR0A |= _BV(UDRE0);
    //UCSR0B |= _BV(TXEN0) | _BV(RXEN0);

    enable_receiving();
}

static inline void enable_transmission(void) {
    UCSR0B |= _BV(UDRIE0);
}

static inline void enable_receiving(void) {
    UCSR0B |= _BV(UDRIE0);
    UCSR0B |= _BV(RXCIE0);
}

static inline void disable_transmission(void) {
    UCSR0B &= ~_BV(UDRIE0);
}

static inline buf_status_t buffer_write(volatile buffer_t *buffer, char c) {
    // copy a char to internal buffer
    unsigned char next = (buffer->head + 1) % BUF_SZ;

    if(next == buffer->tail)
        return BUFFER_FULL;

    buffer->data[buffer->head] = c;
    buffer->head = next;
    return BUFFER_OK;
}

static inline buf_status_t buffer_read(volatile buffer_t *buffer, char *c) {
    // read a char from internal buffer
    if(buffer->head == buffer->tail)
        return BUFFER_EMPTY;

    *c = buffer->data[buffer->tail];
    buffer->tail = (buffer->tail + 1) % BUF_SZ;
    return BUFFER_OK;
}

ISR(USART_UDRE_vect) {
    char c = 0;
    if(buffer_read(&tx_buffer, &c) == BUFFER_OK)
        // write char to usart
        UDR0 = c;
    else
        // when buffer is empty switch off interrupts
        disable_transmission();
}

ISR(USART_RX_vect) {
    // wait for usart receive to complete
    while(!(UCSR0A & _BV(RXC0)))
        ;

    // TODO: add checking??
    buffer_write(&rx_buffer, UDR0);
}

unsigned char uart_tx_complete(void) {
    return UCSR0A & _BV(UDRE0);
}

// wrapper to read from ram or flash based no mem_loc
static char read_byte(const char *data, mem_type_t mem_loc) {
    if(mem_loc == FLASH)
        return pgm_read_byte(data);
    else if(mem_loc == RAM)
        return *data;
    else
        // unsupported memory type
        return 0;
}

static void print_str(char *ptr) {
    while(*ptr)
        usart_putc(*ptr++);
}

static void usart_puts_T(const char *data, mem_type_t type) {

    // write to buffer while it's not full
    while(read_byte(data, type) != '\0' &&
        buffer_write(&tx_buffer, read_byte(data++, type)) == BUFFER_OK)
        ;

#ifndef SERIAL_USART
    // enable usart interrupt to start data transfer
    enable_transmission();

#else // SERIAL_USART
    // wait for usart buffer and write data there
    //while(read_byte(data, type) != '\0')
        //usart_putc(read_byte(data++, type));

    char c;
    while(buffer_read(&tx_buffer, &c) == BUFFER_OK)
        usart_putc(c);

#endif // SERIAL_USART

}

// read string from flash
void usart_puts_P(const char *data) {
    return usart_puts_T(data, FLASH);
}

// read string from ram
void usart_puts(const char *data) {
    return usart_puts_T(data, RAM);
}

#include<stdio.h>
// copy string from buffer to user buffer
void usart_gets(char *data) {
    while(buffer_read(&rx_buffer, data++) != BUFFER_EMPTY)
        ;
}

// blocking write to usart
void usart_putc(const char c) {
    while(!(UCSR0A & _BV(UDRE0)))
        ;
    UDR0 = c;
}

// blocking read from usart
unsigned char usart_getc(void) {
    while(!(UCSR0A & _BV(UDRE0)))
        ;
    return UDR0;
}

#include <string.h>
volatile buffer_t _buffer_debug(char buf, char debug) {
    // buf = 0 -> rx_buffer
    // buf = 1 -> tx_buffer
    char buf_str[3];
    buffer_t buffer;

    if(buf == 0) {
        strlcpy(buf_str, "rx", 3);
        buffer = rx_buffer;
    }
    else if(buf == 1) {
        strlcpy(buf_str, "tx", 3);
        buffer = tx_buffer;
    }

    if(debug == 1)
        printf("%s buffer: {head: %d, tail: %d, data: \"%s\"}\n",
               buf_str, buffer.head, buffer.tail, buffer.data);

    return buffer;
}

