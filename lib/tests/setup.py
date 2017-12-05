
# from setuptools import setup, Extension
from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

import os
import platform

stubdir = "stubs/include"

if platform.system() == "Windows":
    compile_args = ["/DTEST"]
    link_args = ["-dll"]
else:
    compile_args = ["-g", "-DTEST"]
    link_args = ["-shared", "-g"]


os.environ["CC"] = "gcc"
os.environ["LDSHARED"] = "gcc"


def find_lib(path):
    ## find all c files needed to compile
    import os
    return ["%s/%s" % (path, f) for f in os.listdir(path) if f.endswith(".c")]


## build separate libs for each pyx file
setup(
    ext_modules=cythonize([
        Extension("py_usart", ["../usart.c", "py_usart.pyx"] +
                              find_lib("stubs/include/avr") +
                              find_lib("stubs/include/util"),
                  include_dirs=[stubdir],
                  extra_compile_args=compile_args,
                  extra_link_args=link_args),
         Extension("py_interrupt", ["../interrupt.c", "py_interrupt.pyx",
                                    "../defs.c"] +
                              find_lib("stubs/include/avr") +
                              find_lib("stubs/include/util"),
                  include_dirs=[stubdir],
                  extra_compile_args=compile_args,
                  extra_link_args=link_args),

    ])
)

