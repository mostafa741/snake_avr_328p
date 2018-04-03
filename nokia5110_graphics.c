/*
* nokia5110_graphics.c
*
* Created: 03-Apr-18 6:04:54 AM
*  Author: mosta
*/
#include "nokia5110_graphics.h"


void set_pixel(uint8_t buffer[BANKS][COLS],uint8_t x,uint8_t y)
{
	SET_BIT_REG(buffer[(x/8)][y],(x%8));
	return;
}

void clear_pixel(uint8_t buffer[BANKS][COLS],uint8_t x,uint8_t y)
{
	CLEAR_BIT_REG(buffer[(x/8)][y],(x%8));
	return;
}

void print_buffer(uint8_t buffer[BANKS][COLS])
{
	uint8_t idx_x,idx_y;
	for (idx_x=0;idx_x<BANKS;idx_x++)
	{		
		for (idx_y=0;idx_y<COLS;idx_y++)
		{
			lcd_goto_xy(idx_x,idx_y);
			lcd_write_data(buffer[idx_x][idx_y]);
		}
	}
	return;
}

void clear_buffer(uint8_t buffer[BANKS][COLS])
{
	uint8_t idx_x,idx_y;
	for (idx_x=0;idx_x<BANKS;idx_x++)
	{
		for (idx_y=0;idx_y<COLS;idx_y++)
		{
			buffer[idx_x][idx_y]=0;
		}
	}
	return;
}

void draw_rect(uint8_t buffer[BANKS][COLS],uint8_t pos_x,uint8_t pos_y,uint8_t width,uint8_t height)
{
	uint8_t i;
	for (i = pos_x; i < (pos_x+width); i++)
	{
		set_pixel(buffer,i,pos_y);
		set_pixel(buffer,i,(pos_y+height)-1);
	}
	
	for (i = pos_y; i < (pos_y+height); i++)
	{
		set_pixel(buffer,pos_x,i);
		set_pixel(buffer,(pos_x+width)-1,i);
	}
	
	return;
}

void draw_solid_rect(uint8_t buffer[BANKS][COLS],uint8_t pos_x,uint8_t pos_y,uint8_t width,uint8_t height)
{
	uint8_t x,y;
	for (x = pos_x; x < (pos_x+width); x++)
	{
		for (y = pos_y; y < (pos_y+height); y++)
		{
			set_pixel(buffer,x,y);
		}
	}
	
	return;
}