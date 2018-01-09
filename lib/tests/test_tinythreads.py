

import unittest
from py_tinythreads import spawn, t_yield, lock, unlock, get_queue_items
from collections import defaultdict


int_TIMER1_COMPB = 0x2
TASK_RUN_COUNT = defaultdict(int)


## for more than 2 callbacks add a cdef c_callback_n to py_rtos.pyx
def task_1(arg):
    global TASK_RUN_COUNT
    TASK_RUN_COUNT["task_1"] += 1
    while True:
        print "task 1"
        t_yield()


def task_2(arg):
    global TASK_RUN_COUNT
    TASK_RUN_COUNT["task_2"] += 1
    while True:
        print "task 2"
        t_yield()


class Test_primes(unittest.TestCase):

    def test_spawn(self):

        spawn(task_1, 1)
        spawn(task_2, 2)

        ts = get_queue_items("freeQ")
        print [t.arg for t in ts]
        ts = get_queue_items("readyQ")
        print [t.arg for t in ts]
        import pdb; pdb.set_trace()

    def test_yield(self):
        ## put thread A on ready q
        ## set current to thread Main
        ## call yield
        ## check current is thread A
        ## check thread Main is on ready q
        pass

    def test_lock(self):
        pass

    def test_unlock(self):
        pass


if __name__ == "__main__":
    unittest.main()

