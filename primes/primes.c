
#include "primes.h"

#ifdef TEST
#include<stdio.h>
#endif

#define BUFSIZ_S 64

void printAt(uint8_t id, uint16_t number) {
    uint8_t pp = id;
    char buf_str[BUFSIZ_S];

#ifndef TEST
    itoa(id, buf_str, BUFSIZ_S);
	uint8_t len = strlen(buf_str);
    strlcpy(buf_str + len, ": ", 3);
    // itoa((number % 100) / 10, buf_str + 10, BUFSIZ_S - 10);
	len = strlen(buf_str);
    itoa(number, buf_str + len, BUFSIZ_S - len);
#else
	snprintf(buf_str, BUFSIZ_S, "%d: %d", id, number);
#endif

    printf("%d %d0, %d\n", number, (number % 100)/ 10, pp);
    usart_puts(buf_str);
    usart_puts(" ");
    pp++;
    printf("%d %d0, %d\n", number, number % 10, pp);
    usart_puts(buf_str);
    usart_puts("\n");
    yield();
}

uint8_t is_prime(uint16_t number) {
    if(number < 1) return 0;
    if(number == 1) return 1;
    if(number == 2) return 1;
    if(number % 2 == 0) return 0;
    for(int i=3; (i*i)<=number; i+=2){
        if(number % i == 0 ) return 0;
    }
    return 1;
}

void computePrimes(uint16_t id) {
    uint16_t n;

    for(n = 1; n < 1000; n++) {
        if (is_prime(n)) {
            printAt(id, n);
        }
    }
}

int runner(void) {
    spawn(computePrimes, 0);
    computePrimes(3);

    return 0;
}

int main(void) {
    return runner();
}
