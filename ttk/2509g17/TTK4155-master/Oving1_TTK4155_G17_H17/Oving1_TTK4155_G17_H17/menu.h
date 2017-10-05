/*
 * menu.h
 *
 * Created: 28.09.2017 20:18:12
 *  Author: dirkpr
 */ 


#ifndef MENU_H_
#define MENU_H_
#include "oled.h"
#include <avr/pgmspace.h>
#include "uart.h"
#include "input_conversion.h"
#include "button_interrupts.h"

#include <stdlib.h>//malloc
typedef struct menu menu;

struct menu  {
	PGM_P title; //title of the menu entries
	int n_sib; //number of siblings
	
	//menu * ptr_self; //pointer to itself
	//menu * ptr_sib_up; //pointer to the sibling above
	menu * ptr_sib_down; //pointer to the sibling bellow
	menu * ptr_child; //pointer to the child 
	menu * ptr_parent; //pointer to the parent
};

void menu_update(void);
void initialize_menu(void);
void setup_menu(menu * new_menu, menu * ptr_sib_down, menu * ptr_parent, menu * ptr_child,int n_sib,PGM_P title);
int navigate_menu(void);
void sram_clear_line(unsigned int line);
#define NAVIGATION_TRHESHOLD 70



void menu_left_button_flag(void);
void menu_right_button_flag(void);
void menu_function_selected(void);

void menu_set_contrast(void);
void menu_calibrate_joystick(void);
#endif /* MENU_H_ */