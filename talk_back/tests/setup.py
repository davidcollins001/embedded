
# from setuptools import setup, Extension
from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

import os

os.environ["CC"] = "gcc"
os.environ["LDSHARED"] = "gcc"


def find_lib(path):
    ## find all c files needed to compile
    import os
    return ["%s/%s" % (path, f) for f in os.listdir(path) if f.endswith(".c")]

print ["../interrupt.c", "../sleep.c",
                                   "../timer.c", "../usart.c", "../talk_back.c",
                                   "py_talk_back.pyx"] + find_lib("lib/avr"),

## build one lib - requires py_talk_back.pyx 'include'ing py_usart.pyx
setup(
    ext_modules = cythonize([
        # Extension("py_talk_back", ["lib/avr/pgmspace.c", "lib/avr/io.c",
                                   # "lib/avr/sleep.c", "lib/avr/wdt.c",
        Extension("py_talk_back", ["py_talk_back.pyx"] + find_lib("..") + \
                                  find_lib("lib/avr"),
                  include_dirs=["..", ".", "lib"],
                  extra_compile_args=["-g"],
                  extra_link_args=["-shared", "-g"]),
    ])
)

## build separate libs for each pyx file
# setup(
    # ## TODO: move into one lib by using a master pyx file
    # ext_modules = [
        # Extension("py_usart", ["lib/avr/pgmspace.c", "lib/avr/io.c",
                               # "../usart.c", "py_usart.pyx"],
                  # include_dirs=["lib"],
                  # extra_link_args=["-shared"]),
        # Extension("py_talk_back", ["lib/avr/pgmspace.c", "lib/avr/io.c",
                                   # "lib/avr/sleep.c", "lib/avr/wdt.c",
                                   # "../interrupt.c", "../sleep.c",
                                   # "../timer.c", "../usart.c",
                                   # "../talk_back.c", "py_talk_back.pyx",
                                   # "py_usart.pyx"],
                  # include_dirs=["../", "lib"],
                  # extra_compile_args=["-g"],
                  # extra_link_args=["-shared", "-g"]),
    # ]
# )

