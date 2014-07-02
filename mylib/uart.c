#include <msp430.h>
#include <string.h>
#include "include/uart.h"
#include "circular_buf.h"

static circular_buf_t snd_buf;
static circular_buf_t rcv_buf;

void uart_init(uart_baud_rate_t baud_rate)
{
    if (baud_rate >= UART_BAUD_RATE_LAST)
        return;

    /* for now we support only 1 Mhz DCO as a clock source */
    if (BCSCTL1 != CALBC1_1MHZ || DCOCTL != CALDCO_1MHZ)
        return;

    UCA0CTL1 |= UCSWRST; // initialization is started by asserting the reset

    UCA0CTL1 |= UCSSEL_2;                   // CLK = SMCLK
    UCA0BR0 = 104;                          // 1 MHz -> 9600
    UCA0BR1 = 0;                            // 1 MHz -> 9600
    UCA0MCTL = UCBRS1;                      // Modulation UCBRSx = 1

#if 0
    UCA0BR0 = 8;                              // 1MHz 115200
    UCA0BR1 = 0;                              // 1MHz 115200
    UCA0MCTL = UCBRS2 + UCBRS0;               // Modulation UCBRSx = 5
#endif

    uart_pins_config();

    UCA0CTL1 &= ~UCSWRST; // finished, remove the reset bit

    IE2 |= UCA0RXIE;               // Enable USCI_A0 RX interrupt
}

int uart_send_buf(unsigned char buf[], int len)
{
    int bytes;

    /* we share "snd_buf" with the interrupt func., so we protect it */
    IE2 &= ~UCA0TXIE;
    bytes = cb_write(&snd_buf, buf, len);
    IE2 |= UCA0TXIE;

    return bytes;
}

int uart_send(unsigned char c)
{
    return uart_send_buf(&c, 1);
}

int uart_blk_send_str(char *str)
{
    int bytes = strlen(str);

    while (bytes)
    {
        bytes -= uart_send_buf((unsigned char *)str, bytes);
        /* if the CLK is 1Mhz this is 100ms */
        __delay_cycles(10000);
    }

    return 0;
}

int uart_recv_buf(unsigned char *buf, int len)
{
    int bytes;

    /* we share "rcv_buf" with the interrupt func., so we protect it */
    IE2 &= ~UCA0RXIE;
    bytes = cb_read(&rcv_buf, buf, len);
    IE2 |= UCA0RXIE;

    return bytes;
}

int uart_recv(unsigned char *c)
{
    return uart_recv_buf(c, 1);
}

void uart_blk_recv(unsigned char *c)
{
    /* if the CLK is 1Mhz this is 100ms delay */
    while (!uart_recv(c))
        __delay_cycles(10000);
}

#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
    unsigned char c;

    /* if the transmitter is busy, get out */
    if (!(IFG2 & UCA0TXIFG))
        return;

    /* nothing to send, turn the interrupt off */
    if (cb_is_empty(&snd_buf))
    {
        IE2 &= ~UCA0TXIE;
        return;
    }

    /* send it! */
    cb_read(&snd_buf, &c, 1);
    UCA0TXBUF = c;
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
    unsigned char c;

    /* if we don't have a char ready, get out */
    if (!(IFG2 & UCA0RXIFG))
        return;

    /* rcv_buf is full, shut down the reception */
    if (cb_is_full(&rcv_buf))
    {
        IE2 &= ~UCA0RXIE;
        return;
    }

    /* recieve one char */
    c = UCA0RXBUF;
    cb_write(&rcv_buf, &c, 1);
}
