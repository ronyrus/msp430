#include <msp430.h>
#include "pwm.h"

void pwm_pin_config(void)
{
	/* Green LED is used for PWM testing */
	P1DIR |= BIT6;
	/* set P1.6 (green led) to TA0 mode */
	P1SEL |= BIT6;
}

void main(void)
{
  WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	/* this sets VLO clock source, without it ACLK is not working */
	BCSCTL3 = LFXT1S_2;

	pwm_init(PWM_20);

	__bis_SR_register(LPM0_bits + GIE);
}
