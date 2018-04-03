/*
* nokia5110_lcd.h
*
* Created: 01-Apr-18 4:26:50 PM
*  Author: mosta
*/


#ifndef NOKIA5110_LCD_H_
#define NOKIA5110_LCD_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "common.h"

#define BANKS (06)
#define ROWS  (48)
#define COLS  (84)

#define LCD_PORT PORTB

#define LCD_DDR  ((*((&LCD_PORT)-1)))

#define LCD_RST		PINB0
#define LCD_DC		PINB1
#define LCD_SCE		PINB2
#define LCD_DIN		PINB3
#define LCD_SCLK	PINB5


void lcd_init(void);

void lcd_write_data(uint8_t data);

void lcd_set_x(uint8_t address);

void lcd_set_y(uint8_t address);

void lcd_goto_xy(uint8_t x,uint8_t y);

void lcd_clr();


#endif /* NOKIA5110_LCD_H_ */