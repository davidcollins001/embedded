
import unittest
from py_flash import init, run1, run2, runner, PORTC, PC1, PC2, PC3

NUM_LEDS = 6


class Test_flash(unittest.TestCase):

    def test_run(self):
        for fun, pin in [(run1, PC1), (run2, PC2)]:
            PORTC(value=0)
            for i in xrange(5):
                fun()
                exp = (not (i % 2)) << pin()
                msg = "expect %s to give %s but got %s" % \
                        (fun.__name__, bin(exp), bin(PORTC()))
                self.assertEqual(PORTC(), exp, msg)

    def test_runner(self):
        PORTC(value=0)

        init()
        ## switches for each led
        pc3 = pc2 = pc1 = 0

        ## each iteration simulates a clock tick
        for i in xrange(48):
            runner()

            ## i % 2 == 3rd led
            ## i % 4 == 2nd led
            ## i % 8 == 1st led
            if not ((i + 1) % 8):
                pc1 ^= 1
            if not ((i + 1) % 4):
                pc2 ^= 1
            # if not ((i + 1) % 2):
                # pc3 ^= 1
            pc3 = int(not (i % 2))

            exp = pc3 << PC3() | pc2 << PC2() | pc1 << PC1()
            msg = "expected %s, but got %s" % (bin(exp), bin(PORTC()))
            self.assertEqual(PORTC(), exp, msg)


if __name__ == "__main__":
    unittest.main()

