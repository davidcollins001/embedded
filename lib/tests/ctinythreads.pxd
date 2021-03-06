
from libc.stdint cimport uint8_t, uint16_t

NTHREADS = 4

ctypedef void (*function_t)(uint16_t)

cdef extern from "embed/tinythreads.h":
    bint initialised

    ctypedef thread_block *thread

    cdef struct thread_block:
        function_t function
        uint16_t arg
        thread next
        # jmp_buf context
        # uint8_t stack[STACKSIZE]

    thread freeQ
    thread readyQ
    thread current

    void spawn(void (*code)(uint16_t), uint16_t arg)
    void t_yield()

    cdef struct mutex_block:
        uint8_t locked
        thread waitQ

    ctypedef mutex_block mutex_t

    void lock(mutex_t *m)
    void unlock(mutex_t *m)

    thread_block threads[4]  # NTHREADS
    thread_block initp

    #define MUTEX_INIT {0,0}
