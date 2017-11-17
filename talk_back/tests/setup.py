
from setuptools import setup, Extension
import os

os.environ["CC"] = "gcc"
os.environ["LDSHARED"] = "gcc"

setup(
    ext_modules = [Extension("py_usart",
                             ["lib/pgmspace.c", "lib/io.c", "../usart.c",
                                 "py_usart.pyx"],
                             include_dirs=["../", "lib"],
                             extra_link_args=["-shared"])]
)

