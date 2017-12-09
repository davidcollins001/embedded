
## must use gmake

CC=avr-gcc
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
CFLAGS=-g -Os -Wall -mmcu=atmega168 -I.

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
TESTS_DIR=tests

all: $(OBJECTS)

%.o: %.c
	$(CC) ${LINKFLAGS} $(CFLAGS) -c $<

.PHONY: clean tests
clean:
	rm -rf $(OBJECTS) $(TARGET).elf $(TARGET).hex $(TARGET).ass
	$(MAKE) -C $(TESTS_DIR) clean

tests:
	$(MAKE) -C $(TESTS_DIR) tests

