
cimport ctinythreads
from libc.stdint cimport uint8_t, uint16_t
# from ctinythreads cimport spawn, yield, lock, unlock

NTHREADS = 4


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
    cdef ctinythreads.function_t function
    cdef int arg
    cdef ctinythreads.thread  next

    ## call this after construction to set args
    cdef cinit(self, ctinythreads.function_t fn, uint16_t arg,
               ctinythreads.thread next):
        self.function = fn
        self.arg = arg
        self.next = next

    @property
    def function(self):
        return self.function(self.arg)

    @property
    def arg(self):
        return self.arg

    @property
    def next(self):
        if self.next is NULL:
            print "NULL"
            return
        t = py_thread()
        t.cinit(self.next.function, self.next.arg, self.next.next)
        return t


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
    print "spawn"
    ctinythreads.spawn(c_callback, arg)
    print "spawn - done"


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

    ts = []
    for t in queue[:NTHREADS]:
        thread = py_thread()
        thread.cinit(t.function, t.arg, t.next)
        ts.append(thread)

    return ts


cdef get_queue_item(q):
    pass

