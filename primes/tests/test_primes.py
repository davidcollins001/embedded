
import unittest
from py_primes import (
    is_prime, computePrimes, printAt, runner, isr_USART_UDRE_vect
)


def _BV(pin):
    return 1 << pin


class Test_primes(unittest.TestCase):

    def setUp(self):
        pass

    def test_is_prime(self):
        exp = [False, True, True, True, False, True, False, True, False, False]
        res = [is_prime(i) for i in xrange(10)]
        self.assertEqual(res, exp)

    # def test_computePrimes(self):
	# computePrimes(0)
	# print isr_USART_UDRE_vect()

    def test_runner(self):
        runner()


if __name__ == "__main__":
    unittest.main()

