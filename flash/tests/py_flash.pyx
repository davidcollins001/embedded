
## include to get all functionality in this extension
include "py_usart.pyx"
include "py_interrupt.pyx"

cimport cflash


def flash(uint8_t choice):
    cflash.flash(choice)


def flash_incr():
    cflash.flash_incr()


def runner():
    return cflash.runner()

