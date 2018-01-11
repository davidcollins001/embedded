
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
    cdef ctinythreads.function_t _function
    cdef int arg
    cdef ctinythreads.thread  next

    ## call this after construction to set args
    cdef cinit(self, ctinythreads.function_t fn, uint16_t arg,
               ctinythreads.thread next):
        self._function = fn
        self.arg = arg
        self.next = next

    cpdef function(self):
        if self._function != NULL:
            return self._function(self.arg)

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
    # cdef thread_block t

    if q == "freeQ":
        queue = ctinythreads.freeQ
    elif q == "readyQ":
        queue = ctinythreads.readyQ

    ts = []
    i = 0
    # for i in xrange(NTHREADS):
    for t in queue[:NTHREADS]:
        try:
        # if t != NULL:
            print ">>>>>>>", i
            # t = queue[i]
            thread = py_thread()
            thread.cinit(t.function, t.arg, t.next)
            ts.append(thread)
        except:
            return ts

    return ts

