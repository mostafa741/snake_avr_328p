/*
 * nokia5110_graphics.h
 *
 * Created: 03-Apr-18 6:05:21 AM
 *  Author: mosta
 */ 


#ifndef NOKIA5110_GRAPHICS_H_
#define NOKIA5110_GRAPHICS_H_

#include <inttypes.h>
#include "common.h"
#include "nokia5110_lcd.h"

void set_pixel(uint8_t buffer[BANKS][COLS],uint8_t x,uint8_t y);

void clear_pixel(uint8_t buffer[BANKS][COLS],uint8_t x,uint8_t y);

void print_buffer(uint8_t buffer[BANKS][COLS]);

void clear_buffer(uint8_t buffer[BANKS][COLS]);

void draw_rect(uint8_t buffer[BANKS][COLS],uint8_t pos_x,uint8_t pos_y,uint8_t width,uint8_t height);

void draw_solid_rect(uint8_t buffer[BANKS][COLS],uint8_t pos_x,uint8_t pos_y,uint8_t width,uint8_t height);


#endif /* NOKIA5110_GRAPHICS_H_ */