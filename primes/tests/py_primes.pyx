
## include to get all functionality in this extension
# include "py_usart.pyx"
# include "py_interrupt.pyx"

cimport cflash
from cflash cimport int8_t, uint8_t


def flash(uint8_t choice):
    cflash.flash(choice)


def flash_incr():
    cflash.flash_incr()


def runner():
    cflash.runner()


def PORTC(value=None):
    if value is not None:
        cflash.PORTC = value
    else:
        return cflash.PORTC


def PINB(value=None):
    if value is not None:
        cflash.PINB = value
    else:
        return cflash.PINB


def PB1(value=None):
    if value is not None:
        cflash.PB1 = value
    else:
        return cflash.PB1


def FLAG_VECT(value=None):
    if value is not None:
        cflash.FLAG_VECT = value
    else:
        return cflash.FLAG_VECT

