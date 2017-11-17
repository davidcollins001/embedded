GCCFLAGS=-g -Os -Wall -mmcu=atmega168 
LINKFLAGS=-Wl,-u,vfprintf -lprintf_flt -Wl,-u,vfscanf -lscanf_flt -lm
AVRDUDEFLAGS=-u -c avr109 -p m168 -b 115200 -P /dev/cuaU0
LINKOBJECTS=../libnerdkits/delay.o ../libnerdkits/lcd.o ../libnerdkits/uart.o

all:	flash.hex

flash.hex:	flash.c
	make -C ../libnerdkits
	avr-gcc ${GCCFLAGS} ${LINKFLAGS} -o flash.o flash.c ${LINKOBJECTS}
	avr-objcopy -j .text -j .data -O ihex flash.o flash.hex

flash.ass:	flash.hex
	avr-objdump -S -d flash.o > flash.ass
	
burn: flash-upload
flash-upload:	flash.hex
	avrdude ${AVRDUDEFLAGS} -U flash:w:flash.hex:a

.PHONY: clean
clean:
	rm -rf flash.hex flash.o

