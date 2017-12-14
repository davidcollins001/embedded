
cimport crtos

ctypedef void (*taskfn_t)()

def init_tasks():
    crtos.init_tasks()

## pass cython callback function to c
cdef void c_set_callback(taskfn_t task):
    print "zzzzzzz"
    crtos.add_task(task)

## cython function that gets called from c
cdef void callcallback():
    global callbackFn
    print "yyyyyyy"
    callbackFn()

c_set_callback(callcallback)

def add_task(callback_task):
    global callbackFn
    print "xxxxxxx", callback_task
    callbackFn = callback_task

def sched():
    crtos.sched()


