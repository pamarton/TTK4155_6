/*
 * button_interrupts.c
 *
 * Created: 21.09.2017 18:11:23
 *  Author: pamarton
 */ 
#include "button_interrupts.h"
uint8_t flag_left_button, flag_right_button;

void initalize_interrupts(void){
	BIT_ON(DDRB, PD2);//enable input
	BIT_ON(DDRB, PD3);
	
	BIT_ON(MCUCR, ISC00);//configuring the interrupts for INT0 on rising edge
	BIT_ON(MCUCR, ISC01);
	
	BIT_ON(MCUCR, ISC10);//configuring the interrupts for INT1 on rising edge
	BIT_ON(MCUCR, ISC11);
	
	BIT_ON(GICR, INT0);//enabling the interrupts INT0 and INT1 in the memory ???????????????????? 21.09.17
	BIT_ON(GICR, INT1);
	
	flag_right_button = 0;
	flag_left_button = 0;
}

uint8_t check_flag_left(void){
	if (flag_left_button == 1)
	{
		flag_left_button = 0;
		return 1;
	}
	return 0;
}

uint8_t check_flag_right(void){
	if (flag_right_button == 1)
	{
		flag_right_button = 0;
		return 1;
	}
	return 0;
}

ISR(INT0_vect){//interrupt button Right
	#if UART_ENABLE
		printf("R_INT\t");
	#endif
	flag_right_button = 1;
}

ISR(INT1_vect){//interrupt button Left
	#if UART_ENABLE
	printf("L_INT\t");
	#endif
	flag_left_button = 1;
}

