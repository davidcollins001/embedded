
## include to get all functionality in this extension
include "py_usart.pyx"
cimport ctalk_back


def talk_back():
    return ctalk_back.talk_back()

def get_cmd(bytes data):
    cdef int count
    cdef char *c_data = data
    cdef char cmd[64]

    count = ctalk_back.get_cmd(c_data, cmd)
    return count, cmd

