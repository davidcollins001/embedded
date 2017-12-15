
import unittest
from py_flash import flash_incr, flash, runner, PORTC, PINB, FLAG_VECT

NUM_LEDS = 6


class Test_flash(unittest.TestCase):

    def setUp(self):
        pass

    def test_flash_incr(self):
        exp = 1
        PORTC(0)
        for i in xrange(8):
            flash_incr()
            self.assertEqual(2 ** (i % 6), PORTC())
            exp <<= 1

    def test_flash(self):
        PORTC(0)
        exp = 0b10101
        for s in xrange(2):
            flash(s)
            exp <<= s
            self.assertEqual(exp, PORTC())

    def test_runner(self):
        PINB(value=0)

        ## each iteration simulates a clock tick
        for i in xrange(20):
            ## set flag as timer interrupt handler would
            FLAG_VECT(value=0x2)
            runner()
            print i, PORTC()


if __name__ == "__main__":
    unittest.main()

