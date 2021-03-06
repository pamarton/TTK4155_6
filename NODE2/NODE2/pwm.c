/*
 * timer.c
 *
 * Created: 17/10/2017 16:04:36
 *  Author: Amund Marton
 */ 

#include "pwm.h"
#include "../../common_library/common.h"
#include "../../common_library/i_o.h"
#include "../../common_library/uart.h"
uint8_t FLAG_refresh_screen;

void pwm_init(double period){	//	Function for initilization of the timers. Period is given in ms
	//Enable output at port E3
	DDRE |= (1 << PE3);
	
	// Use Fast-pwm/mode 14. Compare Table 17.2 on page 145 of the Arduino2560 datasheet. Using  OC3A.
	TCCR3A &= ~(1<<WGM30);
	TCCR3A |= (1<<WGM31);
	TCCR3B |= (1<<WGM33)|(1<<WGM32); //		WGM01: set mode to CTC (reset timer on OCR0)     CS0n:set prescaler (to 1024)	
		
	//Set COM3A_1:0 to 10 to use non-inverted pwm.
	TCCR3A |= (1<<COM3A1);
	TCCR3A &= ~(1<<COM3A0);

	// Set prescaler. Compare Table17-6. Clock Select Bit Description.
	TCCR3B |= (1<<CS32) | (1<<CS30);
	TCCR3B &= ~(1<<CS31);
	
	// Define TOP. Compare Table 17.2.				CHECK THIS DIRK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	pwm_set_period(period);
	

	//ICR3 = F_CPU/128/2;
}

void pwm_set_pulse_width(double val){	//vel is given in nano-seconds
	OCR3A = (int)(SCALAR_IN_MS * val);
}

void pwm_set_period(double period){
	ICR3 = (int)(SCALAR_IN_MS * period);
}