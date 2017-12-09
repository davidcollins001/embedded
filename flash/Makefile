
## must use gmake

CC=avr-gcc
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
LIB_DIR = "../lib"
CFLAGS=-g -Os -Wall -mmcu=atmega168 -I$(LIB_DIR)
LINKFLAGS=-Wl,-u,vfprintf -lprintf_flt -Wl,-u,vfscanf -lscanf_flt -lm
AVRDUDE=avrdude
AVRDUDEFLAGS=-u -c avr109 -p m168 -b 115200 -P /dev/cuaU0

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
LIB_OBJECTS=$(wildcard ../lib/*.c)
TESTS_DIR=tests

TARGET=flash

all:	$(TARGET).hex

%.o: %.c
	$(MAKE) -C $(LIB_DIR)
	$(CC) ${LINKFLAGS} $(CFLAGS) -c $<

$(TARGET).hex: $(OBJECTS) $(LIB_OBJECTS)
	$(CC) ${LINKFLAGS} $(CFLAGS) -o $(TARGET).elf $^
	$(OBJCOPY) -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex

$(TARGET).ass:	$(TARGET).hex
	$(OBJDUMP) -S -d $@ > $<

burn: $(TARGET)-upload
$(TARGET)-upload:	$(TARGET).hex
	$(AVRDUDE) ${AVRDUDEFLAGS} -U flash:w:$(TARGET).hex:a

.PHONY: clean tests
clean:
	rm -rf $(OBJECTS) $(TARGET).elf $(TARGET).hex $(TARGET).ass
	$(MAKE) -C $(LIB_DIR) clean
	$(MAKE) -C $(TESTS_DIR) clean

tests:
	$(MAKE) -C $(TESTS_DIR) tests

