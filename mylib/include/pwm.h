#ifndef _PWM_H_
#define _PWM_H_

/* TA0.1 is used for PWM, so configure a pin that supports it */
extern void pwm_pin_config(void);

typedef enum {
	PWM_10 = 1,
	PWM_20,
	PWM_30,
	PWM_40,
	PWM_50,
	PWM_60,
	PWM_70,
	PWM_80,
	PWM_90,
	PWM_100
} pwm_duty_cycle_t;

void pwm_init(pwm_duty_cycle_t initial_level);
void pwd_set(pwm_duty_cycle_t level);

#endif
