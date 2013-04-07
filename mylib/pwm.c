#include <msp430.h>
#include "include/pwm.h"

void pwd_set(pwm_duty_cycle_t level)
{
	/* 20 ms -> 240 ticks -> 10% */
	TA0CCR1 = 240 * level;
}

void pwm_init(pwm_duty_cycle_t initial_level)
{
  pwm_pin_config();

	// timer input clock is ACLK
	// timer mode is UP to CCR0
	TA0CTL = TASSEL_1 + MC_1;

	// reset/set
	TA0CCTL1 = OUTMOD_7;

	/* set counters: period and duty cycle
	 * 12Khz -> 12 ticks in millisecond
	 * 20 ms -> 240 ticks
	 * 200 ms -> 2400 ticks
	 */
	TA0CCR0 = 2400;
	TA0CCR1 = 240;

	pwd_set(initial_level);
}


