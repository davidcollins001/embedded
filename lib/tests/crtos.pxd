
ctypedef unsigned char uint8_t

ctypedef void (*taskfn_t)()

cdef extern from "embed/rtos.h":
    ctypedef struct task_t:
        taskfn_t task_fn
        uint8_t status

    void init_tasks()
    void add_task(taskfn_t task)
    void sched()


# cdef void cSetCallback(Function1 function):
    # SetCallback(function)

# cdef void callcallback(const_ushort *data, unsigned width, unsigned height):
    # global callbackfunc
    # callbackfunc(data,width,height)

# cSetCallback(callcallback)

# def PySetCallback(callbackFunc):
    # global callbackfunc
    # callbackfunc = callbackFunc



# cdef extern from "cheesefinder.h":
    # ctypedef void (*cheesefunc)(char *name, void *user_data)
    # void find_cheeses(cheesefunc user_func, void *user_data)

# def find(f):
    # find_cheeses(callback, <void*>f)

# cdef void callback(char *name, void *f):
    # (<object>f)(name.decode('utf-8'))

