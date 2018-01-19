
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
#ifndef TEST
#define SETSTACK(buf, a) *((unsigned int*)(buf) + 8) = (unsigned int)a + STACKSIZE - 4; \
                         *((unsigned int*)(buf) + 9) = (unsigned int)a + STACKSIZE - 4
#else
#define SETSTACK(buf, a)
#endif

extern uint8_t initialised;

typedef struct thread_block *thread;
struct thread_block {
    void (*function)(uint16_t);      // code to run
    uint16_t arg;                    // argument to the above
    thread next;                // for use in linked lists
    jmp_buf context;            // machine state
    uint8_t stack[STACKSIZE];   // execution stack space
};

void display_q(thread *q);

extern thread freeQ;
extern thread readyQ;
extern thread current;

extern struct thread_block threads[NTHREADS];
extern struct thread_block initp;

void spawn(void (*function)(uint16_t), uint16_t arg);
void yield(void);

#ifdef TEST
void t_yield(void);
#endif // TEST

typedef struct mutex_block {
    uint8_t locked;
    thread waitQ;
} mutex_t;

#define MUTEX_INIT {0,0}
void lock(mutex_t *m);
void unlock(mutex_t *m);

#endif // _TINYTHREADS_H

