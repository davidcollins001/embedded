
#include "thread.h"

void printAt(uint8_t id, uint16_t num) {
    uint8_t pp = id;
    char buf_str[64];

    itoa(id, buf_str, sizeof(buf_str));
#ifdef _WIN32
    strncpy_s(buf_str + 5, sizeof(buf_str) - 5, ": ", 2);
#else
    strlcpy(buf_str + 3, ": ", 2);
#endif
    itoa((num % 100) / 10, buf_str + 10, sizeof(buf_str) - 10);

    usart_puts(buf_str);
    pp++;
    usart_puts(buf_str);
}

uint8_t is_prime(uint16_t i) {
    return 0;
}

void computePrimes(uint8_t id) {
    uint16_t n;

    for(n = 1; ; n++) {
        if (is_prime(n)) {
            printAt(id, n);
        }
    }
}

int main(void) {
    spawn(computePrimes, 0);
    computePrimes(3);

    return 0;
}
