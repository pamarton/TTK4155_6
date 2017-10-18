/*
 * timer.h
 *
 * Created: 17/10/2017 16:04:52
 *  Author: Amund Marton
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "common.h"
									
//-DECLARATIONS-----------------------------//

int	initialize_timer(uint8_t fps);	//	Function for initilization of the timers 

int	timer_get();	//	function for getting the value of the timer, (1 if the timer is up, 0 if timer is still counting)

void timer_reset();	//	function for resetting the timer

//------------------------------------------//

#endif /* TIMER_H_ */