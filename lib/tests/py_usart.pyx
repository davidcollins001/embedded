
from cusart cimport uint8_t
cimport cusart


def _BV(pin):
    return 1 << pin


def usart_puts(char *data):
    cusart.usart_puts(data)


def usart_gets():
    cdef char c_str[64]
    cdef int len = cusart.usart_gets(c_str)
    cdef bytes py_str = c_str
    return len, py_str


def isr_USART_UDRE_vect():

    ## ensure in state to write
    cusart.UCSR0B = _BV(cusart.UDRIE0)

    data = []
    while cusart.UCSR0B:
        cusart.isr_USART_UDRE_vect()
        data.append(cusart.UDR0)

    ## convert ascii code to char
    data = ''.join(chr(r) for r in data)
    return data


def isr_USART_RX_vect(data):
    cdef char c
    ## convert python to c string
    cdef char *c_data = data

    ## ensure in state to write
    print "RXC ", bin(cusart.RXC0), _BV(cusart.RXC0), cusart.UDRIE0, _BV(cusart.UDRIE0)
    cusart.UCSR0A = _BV(cusart.RXC0)

    for c in c_data:
        cusart.UDR0 = c
        cusart.isr_USART_RX_vect()


def buffer_debug(buf=1, debug=False):
    ## buf == 0 > rx buffer
    ## buf == 1 > tx buffer
    return cusart._buffer_debug(buf, debug)

