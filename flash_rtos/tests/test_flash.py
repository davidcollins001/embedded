
import unittest
from py_flash import init, runner, PORTC, PC1, PC2, PC3
import py_flash

NUM_LEDS = 6


class Test_flash(unittest.TestCase):

    def test_runner(self):
        PORTC(value=0)

        py_flash.PC3 = 16
        init()

        print bin(PORTC())
        ## each iteration simulates a clock tick
        for i in xrange(28):
            print i, bin(PORTC()),
            runner()
            print

        print ">>>", PC3


if __name__ == "__main__":
    unittest.main()

