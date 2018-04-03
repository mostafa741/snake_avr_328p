/*
* snake_game.c
*
* Created: 03-Apr-18 8:51:43 AM
*  Author: mosta
*/
#include "snake_game.h"

static uint8_t snake_size;

void snake_init(snake_part_t snake[MAX_SNAKE_SIZE],uint8_t initial_size)
{
	uint8_t idx;
	for (idx = 0; idx < MAX_SNAKE_SIZE ; idx++)
	{
		snake[idx].dirction=DIR_NULL;
	}
	
	for (idx = 0; idx < initial_size ; idx++)
	{
		snake[idx].dirction=DIR_RIGHT;
		snake[idx].pos_x=1;
		snake[idx].pos_y=((initial_size-idx-1)*SNAKE_PART_WIDTH)+1;
	}
	
	snake_size=initial_size;
	
	return;
}

void draw_snake(uint8_t buffer[BANKS][COLS],snake_part_t snake[MAX_SNAKE_SIZE])
{
	uint8_t idx;
	
	for (idx=0;idx<snake_size;idx++)
	{
		draw_solid_rect(buffer,snake[idx].pos_x,snake[idx].pos_y,SNAKE_PART_WIDTH,SNAKE_PART_HEIGHT);
	}
	
	return;
}

void draw_prey(uint8_t buffer[BANKS][COLS],snake_part_t prey)
{
	if (prey.dirction!=DIR_NULL)
	{
		draw_solid_rect(buffer,prey.pos_x,prey.pos_y,SNAKE_PART_WIDTH,SNAKE_PART_HEIGHT);
	}
	return;
}


void refresh_snake(snake_part_t snake[MAX_SNAKE_SIZE],snake_part_t *prey)
{
	uint8_t idx;
	
	
	for (idx=snake_size-1;idx>SNAKE_HEAD_INDEX;idx--)
	{
		snake[idx].dirction=snake[idx-1].dirction;
		snake[idx].pos_x=snake[idx-1].pos_x;
		snake[idx].pos_y=snake[idx-1].pos_y;
	}
	
	switch (snake[SNAKE_HEAD_INDEX].dirction)
	{
		case DIR_RIGHT:
		snake[SNAKE_HEAD_INDEX].pos_y+=SNAKE_PART_WIDTH;
		break;

		case DIR_LEFT:
		snake[SNAKE_HEAD_INDEX].pos_y-=SNAKE_PART_WIDTH;
		break;

		case DIR_UP:
		snake[SNAKE_HEAD_INDEX].pos_x-=SNAKE_PART_HEIGHT;
		break;

		case DIR_DOWN:
		snake[SNAKE_HEAD_INDEX].pos_x+=SNAKE_PART_HEIGHT;
		break;

		default:

		break;
	}
	
	if ((snake[(snake_size-1)].pos_x==prey->pos_x)&&(snake[(snake_size-1)].pos_y==prey->pos_y)&&(prey->dirction!=DIR_NULL))
	{
		snake[snake_size]=snake[(snake_size-1)];
		prey->dirction=DIR_NULL;
		snake_size++;
	}
	
	
	
	return;
}


void set_snake_dir(snake_part_t snake[MAX_SNAKE_SIZE],uint8_t dir)
{
	uint8_t mod1=(snake[SNAKE_HEAD_INDEX].dirction%2);
	uint8_t mod2=(dir%2);
	
	if (mod1!=mod2)
	{
		snake[SNAKE_HEAD_INDEX].dirction=dir;
	}
	
	return;
}


game_state_t check_lose(snake_part_t snake[MAX_SNAKE_SIZE])
{
	uint8_t idx=0;
	snake_part_t head=snake[SNAKE_HEAD_INDEX];
	game_state_t ret=IN_PROGRESS;
	
	//Check if the snake is going to eat itself :D
	for (idx=SNAKE_HEAD_INDEX+1;idx<snake_size;idx++)
	{
		if ((head.pos_x==snake[idx].pos_x)&&(head.pos_y==snake[idx].pos_y))
		{
			ret=LOST;
		}
	}
	
	//Check if the snake is hitting the border
	
	if (((head.pos_x+SNAKE_PART_HEIGHT)>=(ROWS))||((head.pos_y+SNAKE_PART_WIDTH-1)>=(COLS)))
	{
		ret=LOST;
	}
	
	else if (((head.pos_x)<=0)||((head.pos_y)<=0))
	{
		ret=LOST;
	}
	
	return ret;
}

void generate_snake_prey(snake_part_t snake[MAX_SNAKE_SIZE],snake_part_t *pery)
{
	if (pery->dirction==DIR_NULL)
	{
		pery->dirction=DIR_UP;
		
		pery->pos_x=1+((rand()%15)*3);
		pery->pos_y=1+((rand()%27)*3);
	}	
	
	return;
}
