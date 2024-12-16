# Makefile
MCU=atmega328
F_CPU=8000000
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET=main
SRCS=main.c
SERIAL=-P /dev/ttyUSB0 -b 57600

all:
	${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex

flash:
	# avrdude -p ${MCU} -c arduino -U flash:w:${TARGET}.hex:i ${SERIAL} 
	minipro -p "ATMEGA328@DIP28" -E

	minipro -p "ATMEGA328@DIP28" -c code -w main.hex -e
	# minipro -p "ATMEGA328@DIP28" -c code -w main.bin -e -s
	minipro -p "ATMEGA328@DIP28" -c config -w fuses.cfg -e 

clean:
	rm -f *.bin *.hex
