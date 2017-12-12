
#ifndef IO_
#define IO_

#include<stdint.h>

extern uint8_t INT0;

extern uint8_t DDRC;
extern uint8_t ADCSRA;
extern uint8_t EIFR;

extern uint8_t INTF0;
extern uint8_t INTF1;

extern uint8_t TXEN0;
extern uint8_t RXEN0;
extern uint8_t RXCIE0;
extern uint8_t RXC0;

extern uint8_t PCICR;
extern uint8_t PCIE2;
extern uint8_t PCIF2;
extern uint8_t PCINT16;
extern uint8_t PCMSK2;

extern uint8_t DDRB;
extern uint8_t DDRC;
extern uint8_t PORTC;
extern uint8_t PINB;
extern uint8_t PB1;

extern uint8_t UBRR0H;
extern uint8_t UBRR0L;
extern uint8_t UCSR0A;
extern uint8_t UCSR0B;
extern uint8_t UDRIE0;
extern uint8_t UDRE0;
extern uint8_t UDR0;

extern uint8_t TCCR1B;
extern uint8_t TCNT1;
extern uint8_t CS10;
extern uint8_t CS12;
extern uint8_t WGM12;
extern uint8_t OCR1A;
extern uint8_t TIMSK1;
extern uint8_t OCIE1B;

extern uint8_t MCUSR;
extern uint8_t WDTCSR;
extern uint8_t WDIE;
extern uint8_t WDE;
extern uint8_t WDP3;
extern uint8_t WDP0;

extern uint8_t EIMSK;
extern uint8_t EICRA;
extern uint8_t ISC00;
extern uint8_t ISC01;

#endif //IO_

