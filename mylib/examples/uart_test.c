#include <msp430.h> 
#include "uart.h"

void uart_pins_config(void)
{
  /* set P1.1 to UCA0RXD and set P1.2 to UCA0TXD */
  P1SEL |= BIT1 + BIT2;
  P1SEL2 |= BIT1 + BIT2;
}

void echo(void)
{
  char c = 0;

  do {
    while (!uart_recv((unsigned char *)&c))
      __delay_cycles(50000);
    uart_send(c);
  } while (c != 'q');
}

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

  BCSCTL1 = CALBC1_1MHZ; // Run at 1 Mhz
  DCOCTL = CALDCO_1MHZ;	// Run at 1 Mhz

  P1DIR |= BIT0 + BIT6;
  P1OUT |= BIT6;

  uart_init(UART_BAUD_RATE_9600);
  __bis_SR_register(GIE);
  uart_blk_send_str("Welcome to the Echo server (type q to exit):\n");
  echo();
  P1OUT |= BIT0;
  return 0;
}
