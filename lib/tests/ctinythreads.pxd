
from stdtypes cimport uint8_t, uint16_t


cdef extern from "embed/tinythreads.h":
    void spawn(void (*code)(uint8_t), uint16_t arg)
    void yield()

    # struct thread_block {
        # void (*function)(uint8_t)      // code to run
        # uint16_t arg                    // argument to the above
        # thread next                // for use in linked lists
        # jmp_buf context            // machine state
        # uint8_t stack[STACKSIZE]   // execution stack space
    # }
    # typedef struct thread_block *thread

    # struct thread_block threads[NTHREADS]
    # struct thread_block initp

    # typedef struct mutex_block {
        # int locked
        # thread waitQ
    # } mutex_t

    #define MUTEX_INIT {0,0}
    void lock(mutex_t *m)
    void unlock(mutex_t *m)


