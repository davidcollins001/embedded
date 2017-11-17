
PYTHON=python2

LIBS=$(patsubst %.pyx,%.so,$(wildcard test*.pyx))
TESTS=$(wildcard test*.py)

libs: $(LIBS)
	$(PYTHON) setup.py build_ext --inplace

.PHONY: clean tests
tests: clean libs
	$(PYTHON) $(TESTS)

clean:
	rm -rf build *.so *.c

