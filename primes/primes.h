
#ifndef _THREAD_H_
#define _THREAD_H_

#include <stdlib.h>

#include <embed/tinythreads.h>

uint8_t is_prime(uint16_t i);
void computePrimes(uint8_t id);

void printAt(uint8_t id, uint16_t num);

#endif // _THREAD_H_

