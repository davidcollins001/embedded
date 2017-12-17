
from libc.stdint cimport uint8_t, uint16_t

ctypedef void (*task_t)()

cdef extern from "embed/rtos.h":
    ctypedef struct tcb_t:
        uint8_t id
        uint8_t delay
        uint8_t status

    void init_rtos()
    void add_task(task_t task, uint16_t period)
    void sched()

    uint8_t tasks_num
    tcb_t task_list[]

    cdef struct test:
        uint8_t id
        uint8_t stat

