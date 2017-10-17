/*
 * can.h
 *
 * Created: 16.10.2017 10:46:45
 *  Author: pamarton
 */ 


#ifndef CAN_H_
#define CAN_H_

#include "MCP2515.h"
#include "MCP2515_driver.h"
#include "SPI.h"
#include <avr/interrupt.h>


void CAN_initialize(void);

#define CANINTE 0x2B


typedef struct CAN_message_t{
	int id;
	uint8_t length;
	uint8_t data[8];
} CAN_message_t;



CAN_message_t* CAN_message_receive(void);
void CAN_send_byte(CAN_message_t* message,uint8_t n);
void CAN_message_send(uint8_t *data);//array of uint8_t as input
void CAN_construct_meassage(int id, uint8_t length, uint8_t *data);
uint8_t CAN_transmit_complete(void);



ISR(INT2_vect);

#endif /* CAN_H_ */