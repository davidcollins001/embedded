
ctypedef unsigned char uint8_t
ctypedef void (*taskfn_t)()

cdef extern from "embed/rtos.h":
    ctypedef struct task_t:
        taskfn_t task_fn
        uint8_t status

    void init_tasks()
    void add_task(task)
    void sched()

