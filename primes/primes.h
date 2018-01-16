
#ifndef _THREAD_H_
#define _THREAD_H_

#include <stdlib.h>

#include <embed/tinythreads.h>

uint8_t is_prime(uint16_t number);
void computePrimes(uint16_t id);

void printAt(uint8_t id, uint16_t number);

int runner(void);

#endif // _THREAD_H_

