MCU = msp430g2553

UART_OBJS = uart.o circular_buf.o
UART_TARGET = libuart.a
 
PWM_OBJS = pwm.o
PWM_TARGET = libpwm.a

LIBS = $(UART_TARGET) $(PWM_TARGET)
OBJS = $(UART_OBJS) $(PWM_OBJS)

CC = msp430-gcc
AR = msp430-ar

CFLAGS =-Os -Wall --static -g -mmcu=$(MCU)

all : $(LIBS)
 
$(UART_TARGET) : $(UART_OBJS)
	$(AR) cr $@ $^
 
$(PWM_TARGET) : $(PWM_OBJS)
	$(AR) cr $@ $^

%.o : %.c 
	$(CC) $(CFLAGS) -c $<

clean:
	rm -fr $(OBJS) $(LIBS)
