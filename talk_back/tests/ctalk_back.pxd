
cdef extern from "../talk_back.h":
    int talk_back()
    int get_cmd(char *data, char *cmd)

