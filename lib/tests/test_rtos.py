
import unittest
from py_rtos import init_rtos, add_task, sched, tasks_num, task_list
from collections import defaultdict

RUNNABLE = 0x1
RUNNING = 0x2
STOPPED = 0x3

MAX_TASKS = 5 + 1  # 5 tasks + idle task
TASK_RUN_COUNT = defaultdict(int)


## for more than 2 callbacks add a cdef c_callback_n to py_rtos.pyx
def task_1():
    global TASK_RUN_COUNT
    TASK_RUN_COUNT["task_1"] += 1

def task_2():
    global TASK_RUN_COUNT
    TASK_RUN_COUNT["task_2"] += 1


class Test_rtos(unittest.TestCase):

    def setUp(self):
        global TASK_RUN_COUNT
        for task in ["task_1", "task_1"]:
            TASK_RUN_COUNT[task] = 0
        tasks_num(0)

    def test_init_tasks(self):
        ## set tasks_num to check init_rtos sets it correctly
        tasks_num(1)

        init_rtos()
        self.assertEqual(tasks_num(), 1, "expect tasks_num to be 1")

        attrs = [("id", 0),
                 ("delay", 0),
                 ("status", STOPPED)]

        ## check task list has been set up correctly
        tasks = task_list()
        self.assertEqual(tasks[0]["status"], RUNNABLE,
                         "expect first task (idle) to be RUNNABLE")
        for task in tasks[1:]:
            for attr, state in attrs:
                msg = "expect task to have %s %d (%d)" % (attr, state,
                                                          task[attr])
                self.assertEqual(task[attr], state, msg)

    def test_add_task(self):
        init_rtos()

        ## init_rtos adds idle task
        tasks = 1
        self.assertEqual(tasks_num(), tasks,
                         "should be %d task added: %d" % (tasks, tasks_num()))

        for i in xrange(10):
            if tasks < MAX_TASKS:
                tasks += 1
            add_task(task_1, 100)

            msg = "should be %d tasks added: %d" % (tasks, tasks_num())
            self.assertEqual(tasks_num(), tasks, msg)

        def incr():
            for i in xrange(1, MAX_TASKS):
                yield i

        attrs = [("id", incr()),
                 ("delay", 100),
                 ("status", RUNNABLE)]

        ## check task list has been set up correctly
        tasks = task_list()
        self.assertEqual(tasks[0]['status'], RUNNABLE,
                         "expect first task (idle) to be RUNNABLE")
        for task in tasks[1:]:
            for attr, state in attrs:
                try:
                    state = next(state)
                except TypeError:
                    pass

                msg = "expect task to have %s %d (%d)" % (attr, state,
                                                          task[attr])
                self.assertEqual(task[attr], state, msg)

    def test_sched(self):
        cases = [("task_1", 5),
                 ("task_2", 1)]

        init_rtos()

        ## add two tasks to be run
        add_task(task_1, 10)
        add_task(task_2, 50)

        ## run enough iterations (interrupts) to see behaviour
        for _ in xrange(50):
            sched()

        for task, exp in cases:
            msg = "expected scheduler to run %s %d times: %d" % \
                    (task, exp, TASK_RUN_COUNT[task])
            self.assertEqual(TASK_RUN_COUNT[task], exp, msg)


if __name__ == "__main__":
    unittest.main()

