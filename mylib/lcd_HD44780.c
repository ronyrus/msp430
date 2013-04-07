#include <msp430.h>
#include "lcd_HD44780.h"

/* instruction/data register selector */
#define IR do{ lcd_pin_clr(RS_PIN); }while (0)
#define DR do{ lcd_pin_set(RS_PIN); }while (0)

/* read/write selector */
#define WRITE do{ lcd_pin_clr(RW_PIN); }while (0)
#define READ do{ lcd_pin_set(RW_PIN); }while (0)

/* signal the operation */
#define PULSE do { \
		lcd_pin_set(E_PIN); \
		__delay_cycles(1200000); \
		lcd_pin_clr(E_PIN); \
		__delay_cycles(1200); \
} while(0)

static void wait_busy_flag(void)
{
#if 1
	do {
		__delay_cycles(1200);
		READ;
		IR;
		PULSE;
	} while (lcd_pin_get(D7_PIN));
#else
	__delay_cycles(500);
#endif
}

/* Display on/off control */
#define DISPLAY_ON(one_or_zero) (0x8 | ((one_or_zero) << 2))
#define CURSOR_ON(one_or_zero) (0x8 | ((one_or_zero) << 1))
#define CURSOR_BLINK(one_or_zero) (0x8 | ((one_or_zero) << 0))

/* Entry mode set */
#define CURSOR_MOV_DIR(one_or_zero) (0x4 | ((one_or_zero) << 1))
#define DISP_SHIFT_ON(one_or_zero) (0x4 | ((one_or_zero) << 0))

/* Function set */
#define DATA_LENGTH_8_BIT(one_or_zero) (0x20 | ((one_or_zero) << 4))
#define DISPLAY_2_LINES(one_or_zero) (0x20 | ((one_or_zero) << 3))
#define FONT_BIG(one_or_zero) (0x20 | ((one_or_zero) << 2))

static inline void send_byte(char byte, int is_cmd)
{
	wait_busy_flag();
	WRITE;
	if (is_cmd)
		IR;
	else
		DR;

	/* we assume that the interface is 4bit */
	lcd_set_4bit(byte & 0xF0);
	PULSE;

	wait_busy_flag();
	WRITE;
	if (is_cmd)
		IR;
	else
		DR;
	lcd_set_4bit(byte << 4);
	PULSE;
}

#define send_cmd(cmd) send_byte((cmd), 1)
#define send_data(data) send_byte((data), 0)

void lcd_send_char(char c)
{
	send_data(c);
}

void lcd_init(void)
{
	lcd_pin_config();
	__delay_cycles(1000);

	send_cmd(DATA_LENGTH_8_BIT(0)|DISPLAY_2_LINES(1)|FONT_BIG(0));

	send_cmd(DISPLAY_ON(0)|CURSOR_ON(0)|CURSOR_BLINK(0));
	send_cmd(DISPLAY_ON(1)|CURSOR_ON(1)|CURSOR_BLINK(1));
	send_cmd(CURSOR_MOV_DIR(1)|DISP_SHIFT_ON(0));
}

