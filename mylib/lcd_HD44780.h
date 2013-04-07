#ifndef LCD_HD44780_H_
#define LCD_HD44780_H_

/* For now the following assumptions (limitations) are made:
 * - working in 4bit mode (i.e only D04-D7 data pins are connected)
 * - RS is connected to ground (we don't support reading from the LCD)
 */


typedef enum {
	RS_PIN = 1,	/* RS: register select: command or data */
	RW_PIN,		/* RW: read-1/write-0 */
	E_PIN,		/* E: enable (clk) - triggered on the falling edge */
	D0_PIN,		/* Dx: data bus */
	D1_PIN,
	D2_PIN,
	D3_PIN,
	D4_PIN,
	D5_PIN,
	D6_PIN,
	D7_PIN
} lcd_pin_t;

extern void lcd_pin_config(void);
extern void lcd_set_4bit(char high_4_bits);
extern char lcd_pin_get(lcd_pin_t pin);
extern void lcd_pin_set(lcd_pin_t pin);
extern void lcd_pin_clr(lcd_pin_t pin);

void lcd_init(void);
void lcd_send_char(char c);

#endif /* LCD_HD44780_H_ */
