
import unittest
from py_talk_back import (
    talk_back, get_cmd, usart_gets, isr_USART_RX_vect, isr_USART_UDRE_vect,
)

RX, TX = 0, 1
DEBUG = 1

class Test_talk_back(unittest.TestCase):

    def test_get_cmd(self):
        ## cbeck when buffer is full
        for _ in xrange(7):
            for msg in ["send str", "exit"]:
                data = "missed command.>%s.junk" % msg
                l, cmd = get_cmd(data)
                self.assertEqual(l, data.rindex('.')-data.index('>')-1)
                self.assertEqual(cmd[:l], data[data.index('>')+1:
                                               data.rindex('.')])

    def test_empty_cmd(self):
        ## cbeck when buffer is full
        data = "missed command.>.junk"
        l, cmd = get_cmd(data)
        self.assertEqual(l, data.rindex('.')-data.index('>')-1)
        self.assertEqual(cmd[:l], data[data.index('>')+1:
                                       data.rindex('.')])

    def test_talk_back(self):
        ## check when buffer is full
        for _ in xrange(7):
            ## prevent infinite running by sending exit command
            data = "junk>exit.>start of second"

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

    def test_settings(self):
        pass


if __name__ == "__main__":
    unittest.main()

