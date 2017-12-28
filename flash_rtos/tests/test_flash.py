
import unittest
from py_flash import flash_incr, flash, PORTC, PINB, PB1

NUM_LEDS = 6
FLASHES = 2 * 5
int_TIMER1_COMPB = 0x2


def _BV(pin):
    return 1 << pin


class Test_flash(unittest.TestCase):

    def setUp(self):
        PORTC(0)

    def test_flash_incr(self):
        exp = 1
        for i in xrange(15):
            flash_incr()
            self.assertEqual(2 ** (i % 6), PORTC())
            exp <<= 1

    def test_flash(self):
        ## user has pressed switch
        PINB(value=_BV(PB1))

        for s in xrange(15):
            exp = 0b10101
            ## check after 2*FLASHES the leds don't change
            exp = exp << (s % 2) if s < 10 else (exp << 1)
            flash()
            msg = "expect PORTC to be incremented: %s got %s" % \
                    (bin(exp), bin(PORTC()))
            self.assertEqual(exp, PORTC(), msg)

            if not s:
                ## switch unpressed
                PINB(value=0)


if __name__ == "__main__":
    unittest.main()

