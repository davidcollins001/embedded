
import unittest
from py_rtos import init_tasks, add_task, sched

def run_in_c():
    print "**********************************************************************"
    print "called from c"
    print "**********************************************************************"

class Test_rtos(unittest.TestCase):

    def test_init_tasks(self):
        init_tasks()
        add_task(run_in_c)
        sched()


if __name__ == "__main__":
    unittest.main()





