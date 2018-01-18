
cimport ctinythreads
from ctinythreads cimport function_t, thread, mutex_t
from libc.stdint cimport uint8_t, uint16_t
# from ctinythreads cimport spawn, yield, lock, unlock


def initialised(value=None):
    if value is not None:
        ctinythreads.initialised = value
    else:
        return ctinythreads.initialised


def current():
    return py_thread().init(ctinythreads.current)


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
    cdef thread _next

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


cdef class py_mutex:
    cdef mutex_t _mutex
    cdef bint locked
    cdef thread _waitQ

    def __cinit__(self):
        self._mutex.locked = 0
        self._mutex.waitQ = NULL

    ## call this after construction to set args
    cdef init(self, mutex_t m):
        self._mutex = m
        self._locked = m.locked
        self._waitQ = m.waitQ
        return self

    @property
    def locked(self):
        return self._mutex.locked

    @property
    def waitQ(self):
        cdef thread t = self._waitQ
        ts = []
        if t:
            print ">>>> ", t.arg
        # return get_queue_items(self)

        while not t_null(t):
            ts.append(py_thread().init(t))
            t = t.next


cdef mutex_t *cmutext(py_mutex m):
    return &m._mutex


def lock(py_mutex):
    ctinythreads.lock(cmutext(py_mutex))


def unlock(py_mutex):
    ctinythreads.unlock(cmutext(py_mutex))


def get_queue_items(queue):
    """get threads from queue, either "freeQ" or "readyQ" """
    cdef thread q
    if isinstance(queue, basestring):
        if queue == "freeQ":
            q = ctinythreads.freeQ
        elif queue == "readyQ":
            q = ctinythreads.readyQ
    else:
        # q = queue._waitQ
        pass

    ## convert queue to list
    ts = []
    cdef thread t = q
    while not t_null(t):
        ts.append(py_thread().init(t))
        t = t.next

    return ts

cdef bint t_null(thread t):
    return t == NULL
