
# from setuptools import setup, Extension
from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

import os
import platform

STUBDIR = "stubs/include"

if platform.system() == "Windows":
    compile_args = ["/DTEST"]
    link_args = ["-dll"]
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


addl_src = {
    "rtos": ["../sleep.c", "../timer.c"]
}

def build_exts():
    exts = []
    for ext in find_lib(".", ext="pyx"):
        name = os.path.splitext(os.path.basename(ext))[0]
	cname = name.split('_')[1]
        csource = ["../%s.c" % cname] + addl_src.get(cname, [])
        sources = csource + [ext, "../defs.c"] + find_lib(STUBDIR, recurse=True)
        exts.append(
            Extension(name,
                      sources,
                      include_dirs=["..", ".", STUBDIR],
                      extra_compile_args=compile_args,
                      extra_link_args=link_args)
        )
    return exts


## build separate libs for each pyx file
setup(
    ext_modules=cythonize(build_exts())
)

