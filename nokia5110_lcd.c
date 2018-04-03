/*
* nokia5110_lcd.c
*
* Created: 01-Apr-18 4:26:31 PM
*  Author: mosta
*/
#include "nokia5110_lcd.h"



static void lcd_write(uint8_t data);
static void lcd_rst_pulse();
static void lcd_write_command(uint8_t command);

void lcd_init(void)
{
	SET_BIT_REG(LCD_PORT,LCD_SCE);
	SET_BIT_REG(LCD_PORT,LCD_RST);
	
	
	
	/*SPI INIT*/
	LCD_DDR=SET_BIT(LCD_RST)|SET_BIT(LCD_DC)|SET_BIT(LCD_SCE)|SET_BIT(LCD_DIN)|SET_BIT(LCD_SCLK);
	
	SPCR=SET_BIT(SPE)|SET_BIT(MSTR)|SET_BIT(SPR1)|SET_BIT(SPR0);
	
	lcd_rst_pulse();
	
	//extended instruction set
	lcd_write_command(0x21);
	
	//SET Temperature Coefficient
	lcd_write_command(0x07);
	
	//SET Bias System
	lcd_write_command(0x17);
	
	//write V OP to register
	//lcd_write_command(0xA0);// for 5 volts
	//lcd_write_command(0x84);// for 3.3 volts
	lcd_write_command(0x9E);// for 4.86 volts
	
	//basic instruction set
	lcd_write_command(0x20);
		
	//normal mode
	lcd_write_command(0x0C);
	
	//inverse video mode
	//lcd_write_command(0x0D);
	lcd_clr();

}


static void lcd_write(uint8_t data)
{
	
	CLEAR_BIT_REG(LCD_PORT,LCD_SCE);
	
	SPDR=data;
	
	
	while (!GET_BIT_REG(SPSR,SPIF));
	SET_BIT_REG(LCD_PORT,LCD_SCE);
	return;
}

static void lcd_rst_pulse()
{
	CLEAR_BIT_REG(LCD_PORT,LCD_SCE);
	CLEAR_BIT_REG(LCD_PORT,LCD_RST);
	SET_BIT_REG(LCD_PORT,LCD_RST);
	SET_BIT_REG(LCD_PORT,LCD_SCE);
}


static void lcd_write_command(uint8_t command)
{
	CLEAR_BIT_REG(LCD_PORT,LCD_DC);
	lcd_write(command);
	
	return;
}

void lcd_write_data(uint8_t data)
{
	SET_BIT_REG(LCD_PORT,LCD_DC);
	lcd_write(data);
	return;
}

void lcd_set_x(uint8_t address)
{
	address&=0x07;
	address%=BANKS;
	SET_BIT_REG(address,6);
	lcd_write_command(address);
	return;
}

void lcd_set_y(uint8_t address)
{
	address&=0x7F;
	address%=COLS;
	SET_BIT_REG(address,7);
	lcd_write_command(address);
	return;
}

void lcd_goto_xy(uint8_t x,uint8_t y)
{
	lcd_set_x(x);
	lcd_set_y(y);
}

void lcd_clr()
{
	uint8_t x,y;
	for (x=0;x<BANKS;x++)
	{
		for (y=0;y<COLS;y++)
		{
			lcd_goto_xy(x,y);
			lcd_write_data(0x00);
		}
	}
}