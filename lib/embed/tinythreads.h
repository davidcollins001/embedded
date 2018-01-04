
#ifndef _TINYTHREADS_H
#define _TINYTHREADS_H

#include <setjmp.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <embed/usart.h>

#define DISABLE()       cli()
#define ENABLE()        sei()
#define STACKSIZE       80
#define NTHREADS        4
#define SETSTACK(buf, a) *((unsigned int*)(buf) + 8) = (unsigned int)a + STACKSIZE - 4; \
                         *((unsigned int*)(buf) + 9) = (unsigned int)a + STACKSIZE - 4

typedef struct thread_block *thread;
struct thread_block {
    void (*function)(uint8_t);      // code to run
    uint16_t arg;                    // argument to the above
    thread next;                // for use in linked lists
    jmp_buf context;            // machine state
    uint8_t stack[STACKSIZE];   // execution stack space
};

struct thread_block threads[NTHREADS];
struct thread_block initp;

void spawn(void (*code)(uint8_t), uint16_t arg);
void yield(void);

typedef struct mutex_block {
    int locked;
    thread waitQ;
} mutex_t;

#define MUTEX_INIT {0,0}
void lock(mutex_t *m);
void unlock(mutex_t *m);

#endif // _TINYTHREADS_H

