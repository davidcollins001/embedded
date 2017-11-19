
cimport cinterrupt


def toggle_interrupt(choice):
    cinterrupt.toggle_interrupt(choice)


def PCIE2(value=None):
    if value:
        cinterrupt.PCIE2 = value
    else:
        return cinterrupt.PCIE2

def PCICR(value=None):
    if value:
        cinterrupt.PCICR = value
    else:
        return cinterrupt.PCICR

