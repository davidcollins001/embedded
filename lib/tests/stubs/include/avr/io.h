
#ifndef IO_
#define IO_

#include<stdint.h>

#define _BV(bit) (1 << (bit))
// #define _BV(bit) bit

// adc register
extern uint8_t ADCSRA;

// UCSR0A register
extern uint8_t UCSR0A;
//
extern uint8_t RXC0;
extern uint8_t TXC0;
extern uint8_t UDRE0;

// UCSR0B register
extern uint8_t UCSR0B;
//
extern uint8_t RXCIE0;
extern uint8_t TXCIE0;
extern uint8_t UDRIE0;
extern uint8_t RXEN0;
extern uint8_t TXEN0;

// PCICR register
extern uint8_t PCICR;
//
extern uint8_t PCIE2;
extern uint8_t PCIE1;
extern uint8_t PCIE0;

// PCIFR register
extern uint8_t PCIFR;
//
extern uint8_t PCIF2;
extern uint8_t PCIF1;
extern uint8_t PCIF0;

// PCMSK register
extern uint8_t PCMSK2;
//
extern uint8_t PCINT16;

// PIN/DDRX i/o registers
extern uint8_t DDRB;
extern uint8_t DDRC;
extern uint8_t PINB;
extern uint8_t PORTC;
//
extern uint8_t PB1;
extern uint8_t PC1;
extern uint8_t PC2;
extern uint8_t PC3;

extern uint8_t UBRR0H;
extern uint8_t UBRR0L;
extern uint8_t UDR0;

// TCCR1B register
extern uint8_t TCCR1B;
extern uint8_t CS10;
extern uint8_t CS11;
extern uint8_t CS12;
extern uint8_t WGM12;

// timer register
extern uint8_t TCNT1;
extern uint8_t OCR1A;

// iterrupt register
extern uint8_t TIMSK1;
//
extern uint8_t OCIE1B;
extern uint8_t OCIEB;

// external interrupt
extern uint8_t EIMSK;
//
extern uint8_t INT1;
extern uint8_t INT0;

// external interrupt register
extern uint8_t EIFR;
//
extern uint8_t INTF0;
extern uint8_t INTF1;

// external interrupt
extern uint8_t EICRA;
//
extern uint8_t ISC01;
extern uint8_t ISC00;

// mcu status register
extern uint8_t MCUSR;
//
extern uint8_t WDRF;
extern uint8_t BORF;

// wacthdog timer regiser
extern uint8_t WDTCSR;
//
extern uint8_t WDIE;
extern uint8_t WDP3;
extern uint8_t WDCE;
extern uint8_t WDE;
extern uint8_t WDP2;
extern uint8_t WDP1;
extern uint8_t WDP0;

#endif //IO_

