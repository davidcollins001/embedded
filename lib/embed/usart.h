
#ifndef _USART_H_
#define _USART_H_

#include <stdio.h>
#include <string.h>

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
    uint8_t data[BUF_SZ];
    uint8_t head, tail;
} buffer_t;

// create buffer for usart to put data in
volatile static buffer_t tx_buffer;
volatile static buffer_t rx_buffer;

void init_usart(uint8_t rcv);
void usart_putc(const char c);
char usart_getc(void);

void usart_puts_P(const char *data);
void usart_puts(const char *data);
uint8_t usart_gets(char *data);

uint8_t uart_tx_empty(void);

volatile buffer_t _buffer_debug(char buf, char debug);

// ISRs get created for tests so add prototypes
#ifdef TEST
void isr_USART_UDRE_vect();
void isr_USART_RX_vect();
#endif

#endif //_USART_H_

