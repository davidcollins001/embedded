
#include "io.h"

// adc register
uint8_t ADCSRA = 0x0;

// UCSR0A register
uint8_t UCSR0A = 0x0;
//
uint8_t RXC0 = 7;
uint8_t TXC0 = 6;
uint8_t UDRE0 = 5;

// UCSR0B register
uint8_t UCSR0B = 0x0;
//
uint8_t RXCIE0 = 7;
uint8_t TXCIE0 = 6;
uint8_t UDRIE0 = 5;
uint8_t RXEN0 = 4;
uint8_t TXEN0 = 3;

// PCICR register
uint8_t PCICR = 0x0;
//
uint8_t PCIE2 = 2;
uint8_t PCIE1 = 1;
uint8_t PCIE0 = 0;

// PCIFR register
uint8_t PCIFR = 0x0;
//
uint8_t PCIF2 = 2;
uint8_t PCIF1 = 1;
uint8_t PCIF0 = 0;

// PCMSK register
uint8_t PCMSK2 = 0x0;
//
uint8_t PCINT16 = 0;

// PIN/DDRX i/o registers
uint8_t DDRB = 0;
uint8_t DDRC = 0;
uint8_t PINB = 0;
uint8_t PORTC = 0;
//
uint8_t PB1 = 1;
uint8_t PC1 = 1;
uint8_t PC2 = 2;
uint8_t PC3 = 3;

// USART registes
uint8_t UBRR0H = 0x0;
uint8_t UBRR0L = 0x0;
uint8_t UDR0 = 0x0;

// TCCR1B register
uint8_t TCCR1B = 0x0;
uint8_t CS10 = 0;
uint8_t CS11 = 1;
uint8_t CS12 = 2;
uint8_t WGM12 = 3;

// timer register
uint8_t TCNT1 = 1;
uint8_t OCR1A = 1;

// iterrupt register
uint8_t TIMSK1 = 0x0;
//
uint8_t OCIE1B = 1;
uint8_t OCIEB = 2;

// external interrupt
uint8_t EIMSK = 0x0;
//
uint8_t INT1 = 1;
uint8_t INT0 = 0;

// external interrupt register
uint8_t EIFR = 0x0;
//
uint8_t INTF0 = 0;
uint8_t INTF1 = 1;

// external interrupt
uint8_t EICRA = 0x0;
//
uint8_t ISC01 = 1;
uint8_t ISC00 = 0;

// mcu status register
uint8_t MCUSR = 0x0;
//
uint8_t WDRF = 3;
uint8_t BORF = 2;

// wacthdog timer regiser
uint8_t WDTCSR = 0x0;
//
uint8_t WDIE = 6;
uint8_t WDP3 = 5;
uint8_t WDCE = 4;
uint8_t WDE = 3;
uint8_t WDP2 = 2;
uint8_t WDP1 = 1;
uint8_t WDP0 = 0;

