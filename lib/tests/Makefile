
CYTHON_ARGS := --inplace
ifeq ($(OS), Windows_NT)
	PYTHON := python
	CYTHON_ARGS += --compiler=msvc
else
	PYTHON := python2
endif

LIBS := $(patsubst %.pyx, %.so, $(wildcard *.pyx))
SOURCES = $(wildcard *.pyx) $(wildcard ../*.c)
TESTS := $(wildcard test*.py)
OBJS := $(patsubst %.py, %.c,  $(wildcard test*.py))


# all-test:

tests: $(TESTS) $(LIBS)
	for t in $(TESTS); do \
		$(PYTHON) $$t; \
	done

ctests: test_tinythreads.c ../tinythreads.c
	gcc -g -DTEST -I ../ -I stubs/include/ ../tinythreads.c test_tinythreads.c -o test_tinythreads
	./test_tinythreads.exe


$(LIBS): $(SOURCES) #clean
	$(PYTHON) setup.py build_ext $(CYTHON_ARGS)

.PHONY: clean libs ctests
clean:
	rm -rf build *.so *.c

