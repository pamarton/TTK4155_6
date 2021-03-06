/*
 * SRAM.h
 *
 * Created: 09.11.2017 17:46:29
 *  Author: pamarton
 */ 


#ifndef SRAM_H_
#define SRAM_H_

#include "oled.h"
#include "../../common_library/common.h"

#if UART_ENABLE
#include "../../common_library/uart.h"
#endif

#define S_WITDTH 128
#define S_HEIGHT 64
#define WRITE_HEIGHT = S_HEIGHT/8;

uint8_t sram_read(uint8_t page, uint8_t col);//Read the stored value from the sram
void sram_clear_line(uint8_t line);
void sram_init(void);//initialize the sram
void sram_write(uint8_t rad,uint8_t kol, char data);//overwrites the data in the sram indiscriminately
void sram_write_and(uint8_t rad,uint8_t kol, char data);//compares the existing data in the sram and only keeps the pixels they both have
void sram_write_or(uint8_t rad,uint8_t kol, char data);//writes to the sram, "pastes" on top instead of overwriting
void sram_update_oled(void);//send the data from the sram to the oled
void sram_push_line(uint8_t line);//send a line of data from the sram to the oled
uint8_t sram_pixel(uint8_t x, uint8_t y);//sets 1 pixel in the sram
void sram_draw_new_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);//draws a line in the sram, requires start and end point
void sram_draw_line(uint8_t x0, uint8_t y0);//draws a line in the sram, requires a previous point
void sram_set_point(uint8_t x0, uint8_t y0);//sets a point for the start of lines and circles
uint8_t sram_write_char(char letter);//writes a char in the sram
void sram_write_int(int num);//writes a number to the sram (recursive)
void sram_write_string(char letters[]);//writes a string to the sram. \n is next line
void sram_draw_new_circle(uint8_t x0, uint8_t y0, uint8_t radius);//draws a circle in the sram, requires a point and a radius
void sram_draw_circle(uint8_t radius);//draws a circle in the sram, just requires the radius (using the previous point)
void sram_draw_triangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);//draws a triangle in the sram
void sram_draw_rectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);//draws a rectangle in the sram

void sram_draw_notice_box(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t width);
void sram_write_improtant_information(char letters[]);

void sram_scroll_vertically(uint8_t x, uint8_t y_l, uint8_t y_h, int8_t dir, uint8_t rollower);
	
void sram_scroll_line(uint8_t line, uint8_t scroll);
void sram_scroll_horizontally(uint8_t line, uint8_t lower_col, uint8_t upper_col, uint8_t scroll);
void sram_goto_line(uint8_t line);
void sram_goto_column(uint8_t column);
void sram_render_box(uint8_t column, uint8_t row, char letter, uint8_t box_size);
#endif /* SRAM_H_ */