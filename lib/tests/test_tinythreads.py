

import unittest
from py_tinythreads import spawn, t_yield, lock, unlock, get_queue_items
from collections import defaultdict


int_TIMER1_COMPB = 0x2
TASK_RUN_COUNT = defaultdict(int)


## for more than 2 callbacks add a cdef c_callback_n to py_rtos.pyx
def task(arg):
    global TASK_RUN_COUNT
    ## assume arg is task id
    TASK_RUN_COUNT["task_%d" % arg] += 1
    # while True:
    print "task %d" % arg
    # t_yield()

def task_1(arg):
    task(arg)


def task_2(arg):
    task(arg)


class Test_tinythreads(unittest.TestCase):

    def test_spawn(self):

        spawn(task_1, 1)
        spawn(task_2, 2)
        spawn(task_2, 3)

        ## check freeQ/readyQ get dequeue/enqueue'd correctly
        ts = get_queue_items("readyQ")
        self.assertEqual(len(ts), 3)
        self.assertEqual([t.arg for t in ts], [1, 2, 3])
        ts = get_queue_items("freeQ")
        self.assertEqual(len(ts), 1)
        self.assertEqual([t.arg for t in ts if t], [0])

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

