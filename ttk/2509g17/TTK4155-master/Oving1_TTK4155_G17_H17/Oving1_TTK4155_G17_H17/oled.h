/*
 * oled.h
 *
 * Created: 28.09.2017 16:23:56
 *  Author: dirkpr
 */ 


#ifndef OLED_H_
#define OLED_H_

//------------------------------------------//
//	INCLUDES									//
//------------------------------------------//

#include <avr/io.h>

//------------------------------------------//
//	FUNCTIONS								//
//------------------------------------------//

void write_c(uint8_t cmd);
void write_d(uint8_t data);
void oled_home(void);
void oled_ini(void);
void oled_reset(void);
void oled_goto_line(unsigned int line);
void oled_goto_column(unsigned int column);
void oled_print(char * letters);
void oled_print_effect(char * letters, char effect);
int oled_print_char(char letter);
int oled_print_char_effect(char letter, char effect);
void oled_reset(void);
void oled_clear_line(unsigned int line);
void sram_scroll_data(uint8_t line, uint8_t scroll);
void sram_clear_line(uint8_t line);
void sram_init(void);
void sram_write(int rad,int kol, char data);
void sram_write_and(int rad,int kol, char data);
void sram_write_or(int rad,int kol, char data);
void write_screen(void);
void write_line(uint8_t line);
int sram_pixel(int x, int y);
void sram_draw_line(int x0, int y0, int x1, int y1);
int sram_write_char(char letter);
void sram_write_int(int num);
void sram_write_string(char letters[]);
void sram_draw_circle(int x0, int y0, int radius);
void sram_draw_triangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void sram_draw_rectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

#endif /* OLED_H_ */