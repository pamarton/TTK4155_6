/*
 * timer.c
 *
 * Created: 17/10/2017 16:04:36
 *  Author: Amund Marton
 */ 

#include "timer.h"

uint8_t FLAG_refresh_screen;

void initialize_timer(uint8_t fps){	//	Function for initilization of the timers
	TIMSK |= (1<<OCIE0);//when timer is the same as OCR0 it sends an interrupt
	TCCR0 |= (1<<WGM01)|(1<<CS02)|(1<<CS00);//		WGM01: set mode to CTC (reset timer on OCR0)     CS0n:set prescaler (to 1024)
	OCR0 = (F_CPU/PRESCALER)/fps;//-> 4800Hz. Then we just need to count to (4800Hz/Desired_Fps) to get the amount we need count to. (60fps -> 80)
	FLAG_refresh_screen = 1;//since we are initializing we want to refresh the page
}

uint8_t timer_check_flag(void){	//	function for getting the value of the timer
	return FLAG_refresh_screen;
}

void timer_disable_flag(void){	//	function for getting the value of the timer
	FLAG_refresh_screen = 0;
}

ISR(TIMER0_COMP_vect){//interrupt when Timer_0 is done, resets itself
	FLAG_refresh_screen = 1;
}
