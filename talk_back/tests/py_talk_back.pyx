
## include to get all functionality in this extension
include "../../lib/tests/py_usart.pyx"
include "../../lib/tests/py_interrupt.pyx"

from ctalk_back cimport int8_t, uint8_t
cimport ctalk_back


def toggle_tranceiver(choice):
    ctalk_back.toggle_tranceiver(choice)


def get_cmd():
    cdef int count
    cdef char cmd[64]

    count = ctalk_back.get_cmd(cmd)
    return count, cmd[:count]


def talk_back():
    return ctalk_back.talk_back()


def isr_PCINT2_vect():
    return ctalk_back.isr_PCINT2_vect()


def UCSR0A(value=None):
    if value:
        ctalk_back.UCSR0A = value
    else:
        return ctalk_back.UCSR0A


def UCSR0B(value=None):
    if value:
        ctalk_back.UCSR0B = value
    else:
        return ctalk_back.UCSR0B


def RXEN0(value=None):
    if value:
        ctalk_back.RXEN0 = value
    else:
        return ctalk_back.RXEN0


def TXEN0(value=None):
    if value:
        ctalk_back.TXEN0 = value
    else:
        return ctalk_back.TXEN0


def UDRE0(value=None):
    if value:
        ctalk_back.UDRE0 = value
    else:
        return ctalk_back.UDRE0


def FLAG(value=None):
    if value:
        ctalk_back.FLAG = value
    else:
        return ctalk_back.FLAG

