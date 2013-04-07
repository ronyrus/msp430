UART = uart_test
PWM = pwm_test

# TODO: refactoring needed auto-generate OBJS and TARGETS
TARGETS = $(UART).elf $(PWM).elf
INCLUDES = -I../include

MCU = msp430g2553
CC = msp430-gcc
CFLAGS =-Os -Wall -g -mmcu=$(MCU) $(INCLUDES)
LDFLAGS =-mmcu=$(MCU) -L../

 
all:$(TARGETS)

$(UART).elf : $(UART).o
	$(CC) $< $(LDFLAGS) -luart -o $@
	
$(PWM).elf : $(PWM).o
	$(CC) $< $(LDFLAGS) -lpwm -o $@

%.o : %.c 
	$(CC) $(CFLAGS) -c $<

 
clean:
	rm -fr *.o *.elf
 
erase:
	mspdebug rf2500 "erase"
 
upload_uart:
	mspdebug rf2500 "prog uart_test.elf"
upload_pwm:
	mspdebug rf2500 "prog pwm_test.elf"
 
size:
	msp430-size main.elf
