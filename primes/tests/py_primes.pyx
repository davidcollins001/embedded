
cimport cprimes


def _BV(pin):
    return 1 << pin


def printAt(id_, n):
    cprimes.printAt(id_, n)


def is_prime(n):
    return cprimes.is_prime(n)


def computePrimes(id_):
    cprimes.computePrimes(id_)


def runner():
    return cprimes.runner()

def isr_USART_UDRE_vect():

    ## ensure in state to write
    cprimes.UCSR0B = _BV(cprimes.UDRIE0)

    data = []
    while cprimes.UCSR0B:
        cprimes.isr_USART_UDRE_vect()
        data.append(cprimes.UDR0)

    ## convert ascii code to char
    data = ''.join(chr(r) for r in data)
    return data

