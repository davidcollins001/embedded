
## include to get all functionality in this extension
# include "py_usart.pyx"
# include "py_interrupt.pyx"

cimport cflash
from cflash cimport int8_t


def init():
    cflash.init()


def run1():
    cflash.run1()


def run2():
    cflash.run2()


def runner():
    cflash.runner()


def PORTC(value=None):
    if value is not None:
        cflash.PORTC = value
    else:
        return cflash.PORTC


def PC1(value=None):
    if value is not None:
        cflash.PC1 = value
    else:
        return cflash.PC1


def PC2(value=None):
    if value is not None:
        cflash.PC2 = value
    else:
        return cflash.PC2


def PC3(value=None):
    if value is not None:
        cflash.PC3 = value
    else:
        return cflash.PC3


