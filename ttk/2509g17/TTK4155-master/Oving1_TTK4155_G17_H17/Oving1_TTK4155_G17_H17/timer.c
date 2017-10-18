/*
 * timer.c
 *
 * Created: 17/10/2017 16:04:36
 *  Author: Amund Marton
 */ 

#include "timer.h"
uint8_t FLAG_refresh_screen;

int initialize_timer(uint8_t fps);{	//	Function for initilization of the timers
	TCNT0 = 0x00;//reset timer_0
	TCCR0 |= (1<<COM01)|(1<<COM00)|(1<<CS02)|(1<<CS00);//COM0n: Set OC0 mode (on compare match)		CS0n:set prescaler (to 1024)
	OCR0 = (F_CPU/PRESCALER)/fps;//-> 4800Hz. Then we just need to count to (4800Hz/Desired_Fps) to get the amount we need count to. (60fps -> 80)
	FLAG_refresh_screen = 1;//since we are initializing we want to refresh the page
	//sram_write_string("FPS: ");//OLD CODE, REMOVE
	//sram_write_int(fps);
	//write_screen();
	
	//ENABLE INTERRUPTS, IDK HOW!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	while(1){//REMOVE
		
	}
	return 0;
}




int timer_get(){	//	function for getting the value of the timer
	return FLAG_refresh_screen;
}
void timer_reset(){	//	function for resetting the timer
	FLAG_refresh_screen = 0;
}