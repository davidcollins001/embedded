
import unittest
from py_flash import flash_incr, flash, runner, PORTC, PINB, PB1, FLAG_VECT

NUM_LEDS = 6
FLASHES = 2 * 5
int_TIMER1_COMPB = 0x2


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
        PORTC(value=0)

        ## each iteration simulates a clock tick
        for i in xrange(20):
            ## set flag as timer interrupt handler would
            FLAG_VECT(value=int_TIMER1_COMPB)
            runner()
            msg = "expect PORTC to be incremented: %d got %d" % \
                    (1 << (i % 6), PORTC())
            self.assertEqual(PORTC(), 1 << (i % 6), msg)

    def test_runner_switch(self):
        PINB(value=0)
        PORTC(value=0)

        ## simulate switch press after two clock ticks
        for i in xrange(2):
            ## set flag as timer interrupt handler would
            FLAG_VECT(value=int_TIMER1_COMPB)
            runner()
            msg = "expect PORTC to be incremented: %d got %d" % \
                    (1 << (i % 6), PORTC())
            self.assertEqual(PORTC(), 1 << (i % 6), msg)

        ## after flashes the incremantal restarts from here
        portc = PORTC()

        ## user presses switch now
        PINB(value=PB1())

        exp = 0b10101
        marker = 0
        ## simulate switch press after two clock ticks
        for i in xrange(FLASHES):
            ## set flag as timer interrupt handler would
            FLAG_VECT(value=int_TIMER1_COMPB)
            runner()
            msg = "expect PORTC to flash: %d got %d" % \
                    (exp << marker, PORTC())
            self.assertEqual(PORTC(), exp << marker, msg)
            ## move bits in exp over 1 for second part of flash
            marker ^= 1

        ## simulate switch press after two clock ticks
        for i in xrange(portc, 2):
            ## set flag as timer interrupt handler would
            FLAG_VECT(value=int_TIMER1_COMPB)
            runner()
            msg = "expect PORTC to be incremented: %d got %d" % \
                    (1 << (i % 6), PORTC())
            self.assertEqual(PORTC(), 1 << (i % 6), msg)


if __name__ == "__main__":
    unittest.main()

