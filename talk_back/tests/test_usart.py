
import unittest
from enum import Enum
from py_usart import (
        usart_puts, usart_gets, isr_USART_UDRE_vect, isr_USART_RX_vect,
        buffer_debug
)

BUF_SZ = 64
DEBUG = 0

class Buf(Enum):
    RX = 0
    TX = 1


class TestUsart(unittest.TestCase):

    def test_usart_puts(self):
        self._test_usart_buffers(isr_USART_RX_vect, Buf.RX.value, usart_gets,
                                 Buf.TX.value)

    def test_usart_gets(self):
        self._test_usart_buffers(usart_puts, Buf.TX.value, isr_USART_UDRE_vect,
                                 Buf.RX.value, )

    def _test_usart_buffers(self, sender, snd_buf, receiver, rcv_buf):
        for i in xrange(8):
            data = "%s string %d" % (str(sender.__name__), i)

            ## send data
            sender(data)

            ## check data in ring buffer
            buf = buffer_debug(snd_buf, DEBUG)
            head, tail = buf['head'], buf['tail']
            data_len = (head - tail) % BUF_SZ
            self.assertEqual(data_len, len(data))

            ## read data from buffer
            result = receiver()
            self.assertEqual(result[:data_len], data)

            ## check data in ring buffer
            buf = buffer_debug(rcv_buf, DEBUG)
            head, tail = buf['head'], buf['tail']
            self.assertEqual(head, tail)


if __name__ == "__main__":
    unittest.main()

