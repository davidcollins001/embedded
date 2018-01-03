
import unittest
from py_primes import is_prime, computePrimes, printAt


int_TIMER1_COMPB = 0x2


def _BV(pin):
    return 1 << pin


class Test_primes(unittest.TestCase):

    def setUp(self):
        pass

    def test_is_prime(self):
        for i in xrange(8):
            print is_prime(i)

    def test_computePrimes(self):
        for s in xrange(5):
            print computePrimes(

    def test_runner(self):
        PINB(value=0)
        PORTC(value=0)

        ## each iteration simulates a clock tick
        for i in xrange(20):
            ## set flag as timer interrupt handler would
            FLAG_VECT(value=_BV(int_TIMER1_COMPB))
            runner()
            msg = "expect PORTC to be incremented: %s got %s" % \
                    (bin(_BV(i % 6)), bin(PORTC()))
            self.assertEqual(PORTC(), _BV(i % 6), msg)

    def test_runner_switch(self):
        PINB(value=0)
        PORTC(value=0)

        ## simulate switch press after two clock ticks
        for i in xrange(2):
            ## set flag as timer interrupt handler would
            FLAG_VECT(value=_BV(int_TIMER1_COMPB))
            runner()
            msg = "expect PORTC to be incremented: %s got %s" % \
                    (bin(_BV(i % 6)), bin(PORTC()))
            self.assertEqual(PORTC(), _BV(i % 6), msg)

        ## after primeses the incremantal restarts from here
        portc = PORTC()

        ## user presses switch now
        PINB(value=_BV(PB1()))

        exp = 0b10101
        marker = 0
        ## simulate switch press after two clock ticks
        for i in xrange(primesES):
            ## set flag as timer interrupt handler would
            FLAG_VECT(value=_BV(int_TIMER1_COMPB))
            runner()
            msg = "expect PORTC to primes: %s got %s" % \
                    (bin(exp << marker), bin(PORTC()))
            self.assertEqual(PORTC(), exp << marker, msg)
            ## move bits in exp over 1 for second part of primes
            marker ^= 1

        ## simulate switch press after two clock ticks
        for i in xrange(portc, 2):
            ## set flag as timer interrupt handler would
            FLAG_VECT(value=_BV(int_TIMER1_COMPB))
            runner()
            msg = "expect PORTC to be incremented: %s got %s" % \
                    (bin_BV(i % 6), bin(PORTC()))
            self.assertEqual(PORTC(), _BV(i % 6), msg)


if __name__ == "__main__":
    unittest.main()

