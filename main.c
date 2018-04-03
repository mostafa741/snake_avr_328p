/*
* NOKIA5110_LCD_DRIVER_328P.c
*
* Created: 01-Apr-18 4:25:56 PM
* Author : mosta
*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "nokia5110_lcd.h"
#include "nokia5110_graphics.h"
#include "snake_game.h"
#include "UART_driver.h"


uint8_t buffer[BANKS][COLS];

snake_part_t snake[MAX_SNAKE_SIZE];

snake_part_t snake_prey;

int main(void)
{
	CLEAR_BIT_REG(DDRD,PIND7);
	CLEAR_BIT_REG(DDRD,PIND6);
	CLEAR_BIT_REG(DDRD,PIND5);
	CLEAR_BIT_REG(DDRD,PIND4);
	
	SET_BIT_REG(PORTD,PIND7);
	SET_BIT_REG(PORTD,PIND6);
	SET_BIT_REG(PORTD,PIND5);
	SET_BIT_REG(PORTD,PIND4);
	
	uint8_t i=0;
	
	lcd_init();
	
	snake_init(snake,2);
	
	snake_prey.pos_x=1;
	snake_prey.pos_y=snake[SNAKE_HEAD_INDEX].pos_y+30;
	snake_prey.dirction=DIR_UP;
	
	do
	{
		if(!GET_BIT_REG(PIND,PIND7))
		{
			set_snake_dir(snake,DIR_UP);
		}
		
		if(!GET_BIT_REG(PIND,PIND6))
		{
			set_snake_dir(snake,DIR_RIGHT);
		}
		
		if(!GET_BIT_REG(PIND,PIND5))
		{
			set_snake_dir(snake,DIR_DOWN);
		}
		
		if(!GET_BIT_REG(PIND,PIND4))
		{
			set_snake_dir(snake,DIR_LEFT);
		}
		
		i++;
		draw_rect(buffer,0,0,ROWS-1,COLS-1);
		draw_snake(buffer,snake);
		draw_prey(buffer,snake_prey);
		
		refresh_snake(snake,&snake_prey);
		
		
		/*switch (key)
		{
			case 0x11:
			set_snake_dir(snake,DIR_UP);
			break;

			case 0x22:
			set_snake_dir(snake,DIR_DOWN);
			break;

			case 0x33:
			set_snake_dir(snake,DIR_RIGHT);
			break;

			case 0x44:
			set_snake_dir(snake,DIR_LEFT);
			break;

			default:
			break;
		}*/
		
		
		/*if (i==6)
		{
			//set_snake_dir(snake,DIR_UP);
		}
		if (i==7)
		{
			//set_snake_dir(snake,DIR_RIGHT);
		}
		
		if (i==8)
		{
			set_snake_dir(snake,DIR_DOWN);
		}
		
		if (i==20)
		{
			set_snake_dir(snake,DIR_LEFT);
		}
		
		if (i==25)
		{
			set_snake_dir(snake,DIR_UP);
		}*/
		
		
		print_buffer(buffer);
		clear_buffer(buffer);	
		generate_snake_prey(snake,&snake_prey);		
	} while ((check_lose(snake)!=LOST));
	
	while (1){}
}

