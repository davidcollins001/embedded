
import unittest
from py_talk_back import (
    toggle_tranceiver, get_cmd, talk_back, usart_gets, isr_USART_RX_vect,
    isr_USART_UDRE_vect, isr_PCINT2_vect, UCSR0B, RXEN0, TXEN0
)

RX, TX = 0, 1
ON, OFF = 0, 1
DEBUG = 1

class Test_talk_back(unittest.TestCase):

    def test_get_cmd(self):
        ## cbeck when buffer is full
        for _ in xrange(7):
            for msg in ["send str", "exit"]:
                data = "missed command.>%s.junk" % msg
                isr_USART_RX_vect(data)
                l, cmd = get_cmd()
                self.assertEqual(l, data.rindex('.')-data.index('>')-1)
                self.assertEqual(cmd[:l], data[data.index('>')+1:
                                               data.rindex('.')])

    def test_char_cmd(self):
        ## cbeck when buffer is full
        data = "missed command.>S.junk"
        isr_USART_RX_vect(data)
        l, cmd = get_cmd()
        self.assertEqual(l, data.rindex('.')-data.index('>')-1)
        self.assertEqual(cmd[:l], data[data.index('>')+1:
                                       data.rindex('.')])

    def test_partial_cmd(self):
        ## cbeck when buffer is full
        data = "missed command.>junk"
        isr_USART_RX_vect(data)
        # print "--> ", usart_gets()
        l, cmd = get_cmd()
        print cmd
        self.assertEqual(l, 0)
        self.assertEqual(cmd, "")

    def test_empty_cmd(self):
        ## cbeck when buffer is full
        data = "missed command.>.junk"
        isr_USART_RX_vect(data)
        l, cmd = get_cmd()
        self.assertEqual(l, data.rindex('.')-data.index('>')-1)
        self.assertEqual(cmd[:l], data[data.index('>')+1:
                                       data.rindex('.')])

    def test_toggle_tranceiver(self):
        ## set PCIE2 which is used to set register
        RXEN0(value=2)
        TXEN0(value=4)
        UCSR0B(value=0)

        toggle_tranceiver(ON)
        self.assertEqual(UCSR0B(), RXEN0() | TXEN0())

        toggle_tranceiver(ON)
        self.assertEqual(UCSR0B(), RXEN0() | TXEN0())

        toggle_tranceiver(OFF)
        self.assertNotEqual(UCSR0B(), RXEN0() | TXEN0())

    def test_talk_back(self):
        ## check when buffer is full
        for _ in xrange(7):
            ## prevent infinite running by sending exit command
            data = "junk>exit.>start of second"

            ## set flag for incoming data
            isr_PCINT2_vect()
            ## put data into system and process
            isr_USART_RX_vect(data)
            ret = talk_back()

            ## read data back from usart
            exp = data[data.index('>')+1: data.rindex('.')]
            output = isr_USART_UDRE_vect()
            msg = "Expected \"%s\" but got \"%s\"" % (exp, output)
            self.assertTrue(exp in output, msg)

            msg = "expected 0 exit status, check exit path"
            self.assertEqual(ret, 0, msg)


if __name__ == "__main__":
    unittest.main()

