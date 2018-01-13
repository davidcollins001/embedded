
cimport ctinythreads
from ctinythreads cimport function_t, thread
from libc.stdint cimport uint8_t, uint16_t
# from ctinythreads cimport spawn, yield, lock, unlock


## NOTE: to get C to call a python function (task) send a cython function
##       to C and have the python function stored in a global variable.
##       then call the value stored in the global variable (python function)

## cython function that gets called from c
cdef void c_callback_1(uint16_t arg):
    global callback_fn_1
    callback_fn_1(arg)


## cython function that gets called from c
cdef void c_callback_2(uint16_t arg):
    global callback_fn_2
    callback_fn_2(arg)


cdef class py_thread:
    cdef function_t _function
    cdef int _arg
    cdef thread  _next

    ## call this after construction to set args
    cdef init(self, thread t):
        self._function = t.function
        self._arg = t.arg
        self._next = t.next
        return self

    cpdef function(self):
        if self._function != NULL:
            return self._function(self._arg)

    @property
    def arg(self):
        return self._arg

    @property
    def next(self):
        if not t_null(self._next):
            return py_thread().init(self._next)


def spawn(fn, arg):
    global callback_fn_1, callback_fn_2
    ## store python function for cython callback (that c calls) to call

    ## TODO: make this better
    ## add "next" callback function otherwise same python function is called
    if arg == 1:
        callback_fn_1 = fn
        c_callback = c_callback_1
    else:
        callback_fn_2 = fn
        c_callback = c_callback_2

    ## set callback C calls to cython function
    ctinythreads.spawn(c_callback, arg)


def t_yield():
    ctinythreads.t_yield()


def lock(mutex):
    # ctinythreads.lock(mutex)
    pass


def unlock(mutex):
    # ctinythreads.unlock(mutex)
    pass


def get_queue_items(q):
    """get threads from queue, either "freeQ" or "readyQ" """
    if q == "freeQ":
        queue = ctinythreads.freeQ
    elif q == "readyQ":
        queue = ctinythreads.readyQ

    ## convert queue to list
    ts = []
    cdef thread t = queue
    while not t_null(t):
        ts.append(py_thread().init(t))
        t = t.next

    return ts

cdef bint t_null(thread t):
    return t == NULL
