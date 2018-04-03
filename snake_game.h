/*
* snake_game.h
*
* Created: 03-Apr-18 8:51:33 AM
*  Author: mosta
*/


#ifndef SNAKE_GAME_H_
#define SNAKE_GAME_H_
#include <stdlib.h>
#include "nokia5110_graphics.h"

#define ABS(X) (((X)<0) ? (-(X)):((X)))

#define MAX_SNAKE_SIZE 50

#define DIR_UP		0
#define DIR_DOWN	2
#define DIR_RIGHT	1
#define DIR_LEFT	3
#define DIR_NULL	4


#define SNAKE_HEAD_INDEX	0
#define SNAKE_PART_WIDTH	3
#define SNAKE_PART_HEIGHT	3

typedef struct
{
	uint8_t pos_x:6;
	uint8_t pos_y:7;
	uint8_t dirction:3;
	
}snake_part_t;

typedef enum {LOST=0,IN_PROGRESS=1}game_state_t;


void snake_init(snake_part_t snake[MAX_SNAKE_SIZE],uint8_t initial_size);


void draw_snake(uint8_t buffer[BANKS][COLS],snake_part_t snake[MAX_SNAKE_SIZE]);

void draw_prey(uint8_t buffer[BANKS][COLS],snake_part_t prey);


void refresh_snake(snake_part_t snake[MAX_SNAKE_SIZE],snake_part_t *prey);


void set_snake_dir(snake_part_t snake[MAX_SNAKE_SIZE],uint8_t dir);


void generate_snake_prey(snake_part_t snake[MAX_SNAKE_SIZE],snake_part_t *pery);


game_state_t check_lose(snake_part_t snake[MAX_SNAKE_SIZE]);

#endif /* SNAKE_GAME_H_ */