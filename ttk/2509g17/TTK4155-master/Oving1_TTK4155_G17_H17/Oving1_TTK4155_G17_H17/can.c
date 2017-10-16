/*
 * can.c
 *
 * Created: 16.10.2017 10:46:30
 *  Author: pamarton
 */ 


#include "can.h"
volatile static CAN_message_t CAN_receive_buffer;
static CAN_message_t CAN_send_buffer;


void CAN_initialize(void){
	int i = 1;
	i++;
	EMCUCR &= ~(1<<ISC2);
	GICR |= (1<<INT2);
	MCP2515_bit_modify(CANINTE,0b00000001,0b00000001);
}

CAN_message_t* CAN_message_receive(void){	
	return &CAN_receive_buffer;
}

void CAN_construct_meassage(int id, uint8_t length, uint8_t *data){
	CAN_send_buffer.id = id;
	CAN_send_buffer.length = length;
	for(uint8_t i = 0; i < CAN_send_buffer.length; i++){
		CAN_send_buffer.data[i] = data[i];
	}
}

void CAN_message_send(uint8_t *data){//array of uint8_t as input
	for(uint8_t i = 0; i < CAN_send_buffer.length; i++){
		CAN_send_buffer.data[i] = data[i];
	}
	CAN_send_byte(&CAN_send_buffer,0);
}

void CAN_send_byte(CAN_message_t* message,uint8_t n){
	MCP2515_write(0x31+n*0x10,message->id>>3);//8 most significant bits of the message ID
	MCP2515_write(0x32+n*0x10,message->id<<5);//3 least significant bits of the message ID
	MCP2515_write(0x35+n*0x10,(0b00001111)&(message->length));//Message length
	
	for (uint8_t i = 0; i < message->length;i++)
	{
		MCP2515_write(0x36+n*0x10+i,message->data[i]);//Message data
	}
	
	MCP2515_request_to_send(0x80+(1<<n));
	//printf("ID %i L: %i DATA: %i %i %i %i %i %i %i %i\n",CAN_send_buffer.id,CAN_send_buffer.length,CAN_send_buffer.data[0],CAN_send_buffer.data[1],CAN_send_buffer.data[2],CAN_send_buffer.data[3],CAN_send_buffer.data[4],CAN_send_buffer.data[5],CAN_send_buffer.data[6],CAN_send_buffer.data[7]);
	
}







uint8_t CAN_read(uint8_t adr){
	return MCP2515_read(adr);
}


#define RXBnSIDH 0x61
#define RXBnSIDL 0x62
#define RXBnDLC 0x65
#define RXBnDM 0x66
void CAN_data_receive(uint8_t n) {
	CAN_receive_buffer.id = ((CAN_read(RXBnSIDH + n*0x10)<<3)|(0b11100000 & (CAN_read(RXBnSIDL + n*0x10))>>5));
	CAN_receive_buffer.length = (CAN_read(RXBnDLC + n*0x10) & 0b00001111);
	for (uint8_t m = 0; m < CAN_receive_buffer.length; m++){
		CAN_receive_buffer.data[m] = CAN_read(RXBnDM + m);
	}
	
	MCP2515_bit_modify(MCP_CANINTF,1<<n,0);
	
	printf("ID %i L: %i DATA: %i %i %i %i %i %i %i %i\n",CAN_send_buffer.id,CAN_send_buffer.length,CAN_send_buffer.data[0],CAN_send_buffer.data[1],CAN_send_buffer.data[2],CAN_send_buffer.data[3],CAN_send_buffer.data[4],CAN_send_buffer.data[5],CAN_send_buffer.data[6],CAN_send_buffer.data[7]);
	
	
	
}


ISR(INT2_vect){//interrupt button Left
	CAN_data_receive(0);
}