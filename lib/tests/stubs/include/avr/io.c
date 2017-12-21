
#include "io.h"

// adc register
uint8_t ADCSRA = 0x0;

// UCSR0A register
uint8_t UCSR0A = 0x0;
//
uint8_t RXC0 = 0x8;
uint8_t TXC0 = 0x7;
uint8_t UDRE0 = 0x6;

// UCSR0B register
uint8_t UCSR0B = 0x0;
//
uint8_t RXCIE0 = 0x7;
uint8_t TXCIE0 = 0x6;
uint8_t UDRIE0 = 0x5;
uint8_t RXEN0 = 0x4;
uint8_t TXEN0 = 0x3;

// PCICR register
uint8_t PCICR = 0x0;
//
uint8_t PCIE2 = 0x2;
uint8_t PCIE1 = 0x1;
uint8_t PCIE0 = 0x0;

// PCIFR register
uint8_t PCIFR = 0x0;
//
uint8_t PCIF2 = 0x2;
uint8_t PCIF1 = 0x1;
uint8_t PCIF0 = 0x0;

// PCMSK register
uint8_t PCMSK2 = 0x0;
//
uint8_t PCINT16 = 0x0;

// PIN/DDRX i/o registers
uint8_t DDRB = 0x0;
uint8_t DDRC = 0x0;
uint8_t PINB = 0x0;
uint8_t PORTC = 0x0;
//
uint8_t PB1 = 0x1;
uint8_t PC1 = 0x1;
uint8_t PC2 = 0x2;
uint8_t PC3 = 0x3;

uint8_t UBRR0H = 0x1;
uint8_t UBRR0L = 0x2;
uint8_t UDR0 = 0x4;

// TCCR1B register
uint8_t TCCR1B = 0x0;
uint8_t CS10 = 0x0;
uint8_t CS11 = 0x1;
uint8_t CS12 = 0x2;
uint8_t WGM12 = 0x3;

// timer register
uint8_t TCNT1 = 0x1;
uint8_t OCR1A = 0x1;

// iterrupt register
uint8_t TIMSK1 = 0x0;
//
uint8_t OCIE1B = 0x1;
uint8_t OCIEB = 0x2;

// external interrupt
uint8_t EIMSK = 0x0;
//
uint8_t INT1 = 0x1;
uint8_t INT0 = 0x0;

// external interrupt register
uint8_t EIFR = 0x0;
//
uint8_t INTF0 = 0x0;
uint8_t INTF1 = 0x1;

// external interrupt
uint8_t EICRA = 0x0;
//
uint8_t ISC01 = 0x1;
uint8_t ISC00 = 0x0;

// mcu status register
uint8_t MCUSR = 0x0;
//

// wacthdog timer regiser
uint8_t WDTCSR = 0x0;
//
uint8_t WDIE = 0x6;
uint8_t WDP3 = 0x5;
uint8_t WDCE = 0x4;
uint8_t WDE = 0x3;
uint8_t WDP2 = 0x2;
uint8_t WDP1 = 0x1;
uint8_t WDP0 = 0x0;

