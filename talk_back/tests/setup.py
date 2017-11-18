
from setuptools import setup, Extension
import os

os.environ["CC"] = "gcc"
os.environ["LDSHARED"] = "gcc"

setup(
    ext_modules = [
        Extension("py_usart", ["lib/avr/pgmspace.c", "lib/avr/io.c",
                               "../usart.c", "py_usart.pyx"],
                  include_dirs=["lib"],
                  extra_link_args=["-shared"]),
        Extension("py_talk_back", ["lib/avr/pgmspace.c", "lib/avr/io.c",
                                   "lib/avr/sleep.c", "lib/avr/wdt.c",
                                   # "../interrupt.c", "../sleep.c",
                                   # "../timer.c", "../usart.c",
                                   # "../talk_back.c",
                                   "py_talk_back.pyx"],
                  include_dirs=["../", "lib"],
                  extra_compile_args=["-g"],
                  # extra_link_args=["-shared", "-g"]),
                  extra_link_args=["-g"]),
    ]
)

