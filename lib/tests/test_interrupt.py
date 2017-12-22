
import unittest
from py_interrupt import toggle_interrupt, PCIE2, PCICR

ON, OFF = 0, 1


class Test_interrupt(unittest.TestCase):

    def test_toggle_pcint(self):
        ## set PCIE2 which is used to set register
        # PCIE2(value=8)
        PCICR(value=0)

        toggle_interrupt(ON)
        self.assertEqual(PCICR(), 1 << PCIE2())

        toggle_interrupt(ON)
        self.assertEqual(PCICR(), 1 << PCIE2())

        toggle_interrupt(OFF)
        self.assertNotEqual(PCICR(), 1 << PCIE2())


if __name__ == "__main__":
    unittest.main()

