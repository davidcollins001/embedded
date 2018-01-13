

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


def task_1(arg):
    task(arg)


def task_2(arg):
    task(arg)


class Test_tinythreads(unittest.TestCase):

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


    def test_lock(self):
        pass

    def test_unlock(self):
        pass


if __name__ == "__main__":
    unittest.main()

