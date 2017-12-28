
## include to get all functionality in this extension
# include "py_usart.pyx"
# include "py_interrupt.pyx"

cimport cflash
from cflash cimport int8_t, uint8_t


PB1 = cflash.PB1


def flash():
    cflash.flash()


def flash_incr():
    cflash.flash_incr()


def PINB(value=None):
    if value is not None:
        cflash.PINB = value
    else:
        return cflash.PINB


def PORTC(value=None):
    if value is not None:
        cflash.PORTC = value
    else:
        return cflash.PORTC


