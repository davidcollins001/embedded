
#include "io.h"

unsigned char INT0 = 0x1;

unsigned char ADCSRA = 0x1;
unsigned char EIFR = 0x1;

unsigned char INTF0 = 0x1;
unsigned char INTF1 = 0x2;

unsigned char TXEN0 = 0x1;
unsigned char RXEN0 = 0x2;
unsigned char RXCIE0 = 0x4;
unsigned char RXC0 = 0x8;

unsigned char PCICR = 0x0;
unsigned char PCIE2 = 0x1;
unsigned char PCIF2 = 0x2;
unsigned char PCINT16 = 0x1;
unsigned char PCMSK2 = 0x1;

unsigned char DDRC = 0x1;
unsigned char PORTC = 0x1;

unsigned char UBRR0H = 0x1;
unsigned char UBRR0L = 0x2;
unsigned char UCSR0A = 0x0;
unsigned char UCSR0B = 0x0;
unsigned char UDRIE0 = 0x1;
unsigned char UDRE0 = 0x2;
unsigned char UDR0 = 0x4;

unsigned char TCCR1B = 0x1;
unsigned char CS10 = 0x1;
unsigned char CS12 = 0x1;
unsigned char WGM12 = 0x1;
unsigned char OCR1A = 0x1;
unsigned char TIMSK1 = 0x1;
unsigned char OCIE1B = 0x1;

unsigned char MCUSR = 0x1;
unsigned char WDTCSR = 0x1;
unsigned char WDIE = 0x1;
unsigned char WDE = 0x1;
unsigned char WDP3 = 0x1;
unsigned char WDP0 = 0x1;

