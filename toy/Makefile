# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:funtoy.elf

#additional rules for files
funtoy.elf: ${COMMON_OBJECTS} main.o stateMachines.o state_advance.o buzzer.o p2_interrupt_handler.o switches.o draw.o wdt_handler.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load: funtoy.elf
	msp430loader.sh $^

clean:
	rm -f *.o *~ *.elf
