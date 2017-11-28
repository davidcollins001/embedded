
import unittest
from py_talk_back import (
    toggle_tranceiver, get_cmd, talk_back, isr_USART_RX_vect,
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
                sndx = data.index('>')
                endx = sndx + data[sndx:].index('.')
                self.assertEqual(l, endx - sndx - 1)
                self.assertEqual(cmd[:l], data[sndx + 1: endx])

    def test_char_cmd(self):
        ## cbeck when buffer is full
        data = "missed command.>S.junk"
        isr_USART_RX_vect(data)
        l, cmd = get_cmd()
        sndx = data.index('>')
        endx = sndx + data[sndx:].index('.')
        self.assertEqual(l, endx - sndx - 1)
        self.assertEqual(cmd[:l], data[sndx + 1: endx])

    def __test_partial_cmd(self):
        ## cbeck when command is read partially multiple times
        data1 = "missed command.>start"
        isr_USART_RX_vect(data1)
        l1, cmd = get_cmd()
        sndx = data1.index('>')
        self.assertEqual(abs(l1), len(data1) - sndx - 1)
        self.assertEqual(cmd[:abs(l1)], data1[sndx + 1:])

        data2 = "end command.junk"
        isr_USART_RX_vect(data2)
        l2, cmd = get_cmd(partial_str=cmd)
        endx = data2.index('.')

        full_cmd = data1[l1:] + data2[:endx]
        self.assertEqual(l2, len(full_cmd))
        self.assertEqual(cmd[:l2], full_cmd)

    def test_empty_cmd(self):
        ## cbeck when buffer is full
        data = "missed command.>.junk"
        isr_USART_RX_vect(data)
        l, cmd = get_cmd()
        sndx = data.index('>')
        endx = sndx + data[sndx:].index('.')
        self.assertEqual(l, endx - sndx - 1)
        self.assertEqual(cmd[:l], data[sndx + 1: endx])

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
            sndx = data.index('>')
            endx = sndx + data[sndx:].index('.')
            exp = data[sndx + 1: endx]
            output = isr_USART_UDRE_vect()
            msg = "Expected \"%s\" but got \"%s\"" % (exp, output)
            self.assertTrue(exp in output, msg)

            msg = "expected 1 exit status, check exit path"
            self.assertEqual(ret, 1, msg)


if __name__ == "__main__":
    unittest.main()

