
from setuptools import setup, Extension
import os

os.environ["CC"] = "gcc"
os.environ["LDSHARED"] = "gcc"

setup(
    ext_modules = [Extension("py_usart",
                             ["stubs/pgmspace.c", "stubs/io.c", "../usart.c",
                                 "py_usart.pyx"],
                             include_dirs=["../", "stubs"],
                             extra_link_args=["-shared"])]
)

