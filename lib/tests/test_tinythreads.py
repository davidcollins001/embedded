

import unittest
from mock import patch
import py_tinythreads
from py_tinythreads import (
    spawn, t_yield, lock, unlock, get_queue_items, py_mutex
)
from collections import defaultdict


TASK_RUN_COUNT = defaultdict(int)

tt = False

## for more than 2 callbacks add a cdef c_callback_n to py_rtos.pyx
def task(arg):
    global TASK_RUN_COUNT
    ## assume arg is task id
    TASK_RUN_COUNT["task_%d" % arg] += 1
    print "task ", arg


def task_1(arg):
    task(arg)


def task_2(arg):
    task(arg)


class Test_tinythreads(unittest.TestCase):

    def setUp(self):
        py_tinythreads.initialised = 0

    def test_spawn_yield(self):

        spawn(task_1, 1)
        spawn(task_2, 2)
        spawn(task_2, 3)

        cases = [
            #queue, exp spawn, exp yield
            ("readyQ", [1, 2, 3], []),
            ("freeQ", [0], [0, 1, 2, 3]),
        ]

        ## check freeQ/readyQ get dequeue/enqueue'd correctly
        for queue, exp, _ in cases:
            ts = get_queue_items(queue)
            self.assertEqual(len(ts), len(exp))
            self.assertEqual([t.arg for t in ts], exp)

        t_yield()

        for queue, _, exp in cases:
            ts = get_queue_items(queue)
            self.assertEqual(len(ts), len(exp))
            self.assertEqual([t.arg for t in ts], exp)

        ## check function was called
        counts = TASK_RUN_COUNT.items()
        counts.sort()
        for i in xrange(3):
            self.assertEqual("task_%d" % (i + 1), counts[i][0])
            self.assertEqual(1, counts[i][1])

    def test_mutex(self):

        spawn(task_1, 1)
        spawn(task_2, 2)
        spawn(task_2, 3)

        global tt
        tt = True

        print 'locking', py_tinythreads.current().arg
        m = py_mutex()
        lock(m)
        print 1, py_tinythreads.current().arg
        ## set current to next thread???
        lock(m)
        print 2, py_tinythreads.current().arg
        # lock(m)
        print "locked: ", m.locked
        print m.waitQ
        print TASK_RUN_COUNT
        unlock(m)
        print "unlocked: ", m.locked
        unlock(m)
        print "unlocked: ", m.locked
        print m.waitQ


if __name__ == "__main__":
    unittest.main()

