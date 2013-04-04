#include <msp430.h> 

int main(void)
{
    /* this sets VLO clock source, without it ACLK is not working */
	  BCSCTL3 = LFXT1S_2;

	  /* we use watchdog as an interval timer (with an interrupt) */
    WDTCTL = WDT_ADLY_250;
    IE1 |= WDTIE;

    P1DIR |= BIT0;

    __bis_SR_register(LPM0_bits + GIE);
    return 0;
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
    P1OUT ^= BIT0;
}
