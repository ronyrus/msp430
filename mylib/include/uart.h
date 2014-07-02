#ifndef _UART_H_
#define _UART_H_

extern void uart_pins_config(void);

typedef enum {
	UART_BAUD_RATE_9600,
//	UART_BAUD_RATE_115200,
	UART_BAUD_RATE_LAST
} uart_baud_rate_t;

void uart_init(uart_baud_rate_t baud_rate);

int uart_send(unsigned char c);
int uart_send_buf(unsigned char buf[], int len);
int uart_blk_send_str(char *str);

int uart_recv(unsigned char *c);
int uart_recv_buf(unsigned char *buf, int len);
void uart_blk_recv(unsigned char *c);


#endif
