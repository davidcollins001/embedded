
# from setuptools import setup, Extension
from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

import os
import platform

libdir = "../../lib" #% os.getcwd()
stubdir = "../../lib/tests/stubs/include" #% os.getcwd()

if platform.system() == "Windows":
    compile_args = ["/DTEST"]
    link_args = ["/dll"]
else:
    compile_args = ["-g", "-DTEST"]
    link_args = ["-shared", "-g"]


os.environ["CC"] = "gcc"
os.environ["LDSHARED"] = "gcc"


def find_lib(path, ext="c", recurse=False):
    ## recursively find all c files needed to compile
    files = []
    for f in os.listdir(path):
        if os.path.isdir(os.path.join(path, f)) and recurse:
            files.extend(find_lib(os.path.join(path, f), ext=ext))
        else:
            if f.endswith(ext):
                files.append("%s/%s" % (path, f))

    return files


sources = ["py_talk_back.pyx"] + (
    find_lib(libdir) + find_lib("..") + find_lib(stubdir, recurse=True)
)

## build one lib - requires py_talk_back.pyx 'include'ing py_usart.pyx
setup(
    ext_modules=cythonize([
        Extension("py_talk_back",
                  sources,
                  include_dirs=["..", ".", libdir, stubdir],
                  extra_compile_args=compile_args,
                  extra_link_args=link_args),
    ],
        include_path=["%s/tests" % libdir]
    )
)

