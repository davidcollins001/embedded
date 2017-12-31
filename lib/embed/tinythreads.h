/*
 *
 * tinythreads.h
 *
 */

#ifndef _TINYTHREADS_H
#define _TINYTHREADS_H

#define NULL            0
#define DISABLE()       cli()
#define ENABLE()        sei()
#define STACKSIZE       80
#define NTHREADS        4
#define SETSTACK(buf, a) *((uint8_t *)(buf) + 8) = a + STACKSIZE - 4; \
                         *((uint8_t *)(buf) + 9) = a + STACKSIZE - 4

typedef struct thread_block *thread;
struct thread_block {
    void (*function)(int);      // code to run
    int arg;                    // argument to the above
    thread next;                // for use in linked lists
    jmp_buf context;            // machine state
    uint8_t stack[STACKSIZE];   // execution stack space
};

struct thread_block threads[NTHREADS];
struct thread_block  initp;

typedef struct mutex_block {
    int locked;
    thread waitQ;
} mutex_t;

#define MUTEX_INIT {0,0}
void lock(mutex_t *m);
void unlock(mutex_t *m);

void spawn(void (*code)(int), int arg);
void yield(void);

#endif

