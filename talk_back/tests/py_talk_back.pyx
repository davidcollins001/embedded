
## include to get all functionality in this extension
include "py_usart.pyx"
include "py_interrupt.pyx"

cimport ctalk_back


def toggle_tranceiver(choice):
    ctalk_back.toggle_tranceiver(choice)

def get_cmd():
    cdef int count
    cdef char cmd[64]

    count = ctalk_back.get_cmd(cmd)
    return count, cmd

def talk_back():
    return ctalk_back.talk_back()

def isr_PCINT2_vect():
    return ctalk_back.isr_PCINT2_vect()

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


