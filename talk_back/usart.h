
#ifndef USART_H_
#define USART_H_

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "defs.h"

#define F_CPU 14745600
#define BAUD  9600
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)

typedef enum buf_status {BUFFER_OK, BUFFER_EMPTY, BUFFER_FULL} buf_status_t;
typedef enum mem_type {FLASH, RAM} mem_type_t;

#define BUF_SZ 64
typedef struct buffer {
    char data[BUF_SZ];
    unsigned char head, tail;
} buffer_t;

// create buffer for usart to put data in
volatile static buffer_t tx_buffer = {{}, 0, 0};
volatile static buffer_t rx_buffer = {{}, 0, 0};

void init_usart(void);
void usart_putc(const char c);
unsigned char usart_getc(void);

void usart_puts_P(const char *data);
void usart_puts(const char *data);

void usart_gets(char *data);

unsigned char uart_tx_complete(void);

volatile buffer_t _buffer_debug(char buf, char debug);

#endif //USART_H_

