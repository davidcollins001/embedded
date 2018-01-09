
cimport crtos

ctypedef void (*taskfn_t)()


def init_rtos(rate):
    crtos.init_rtos(rate)

## NOTE: to get C to call a python function (task) send a cython function
##       to C and have the python function stored in a global variable.
##       then call the value stored in the global variable (python function)

## cython function that gets called from c
cdef void c_callback_1():
    global callback_fn_1
    callback_fn_1()


## cython function that gets called from c
cdef void c_callback_2():
    global callback_fn_2
    callback_fn_2()


def add_task(task, period):
    global callback_fn_1, callback_fn_2
    ## store python function for cython callback (that c calls) to call

    ## TODO: make this better
    ## add "next" callback function otherwise same python function is called
    if crtos.tasks_num == 1:
        callback_fn_1 = task
        c_callback = c_callback_1
    else:
        callback_fn_2 = task
        c_callback = c_callback_2


    ## set callback C calls to cython function
    # crtos.add_task(c_callback_1, period)
    crtos.add_task(c_callback, period)


def sched():
    crtos.sched()


def tasks_num(value=None):
    if value is not None:
        crtos.tasks_num = value
    else:
        return crtos.tasks_num


# cdef class Py_tcb_t:
    # cdef crtos.tcb_t _tcb
    # # def __cinit__(self, crtos.tcb_t obj):
        # # self._tcb = obj

    # cdef _setup(self, crtos.tcb_t obj):
        # self._tcb = obj
        # print "obj: ", obj
        # self.id = obj.id
        # self.delay = obj.id
        # self.status = obj.id
        # return self


def task_list(value=None):
    if value is not None:
        # crtos.task_list = value
        # for i in xrange(crtos.tasks_num):
            # tasks[i] = <void *>0
        pass
    else:
        return [crtos.task_list[i] for i in xrange(6)]

