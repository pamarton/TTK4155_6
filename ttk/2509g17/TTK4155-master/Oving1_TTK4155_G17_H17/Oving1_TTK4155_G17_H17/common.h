/*
 * common.h
 *
 * Created: 17/10/2017 16:07:16
 *  Author: Amund Marton
 */ 


#ifndef COMMON_H_
#define COMMON_H_

#define VERSION "l6d2" //version name
#define F_CPU 4915200 // clock frequency in Hz
#define BAUDRATE 9600 // Choosen value for bit sent per second
#define UBBR 32 - 1 //F_CPU/(16*BAUDRATE)-1 //USART BAUD RATE REGISTER VALUE

#include <avr/io.h> //constants for the use of the avr
#define MAX_SIGNAL 0xFF //max value of signals (8bit)
#define MIN_SIGNAL 0 //min value of signals (8bit)

#define PRESCALER 1024 //prescaler for timer

#define CAN_ID 40 //ID of the message (we might change this)
#define CAN_MESSAGE_LENGTH 8//length of can messages

#define RXBnSIDH 0x61
#define RXBnSIDL 0x62
#define RXBnDLC 0x65
#define RXBnDM 0x66



#endif /* COMMON_H_ */