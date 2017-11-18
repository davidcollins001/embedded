
PYTHON=python2

LIBS=$(patsubst %.pyx,%.so,$(wildcard *.pyx))
SOURCES=$(wildcard *.pyx) $(wildcard ../*.c)
TESTS=$(wildcard test*.py)
OBJS=$(patsubst %.py,%.c, $(wildcard test*.py))


# all-test:

tests: $(TESTS) $(LIBS)
	for t in $(TESTS); do \
		$(PYTHON) $$t; \
	done

$(LIBS): $(SOURCES) clean
	$(PYTHON) setup.py build_ext --inplace

.PHONY: clean libs
clean:
	@echo sources - $(SOURCES)
	rm -rf build *.so *.c

