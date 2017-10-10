/*
 * MCP2515_driver.c
 *
 * Created: 10.10.2017 18:08:44
 *  Author: pamarton
 */ 

#include "MCP2515_driver.h"


void MCP2515_initialize(void){
	SPI_initialize();
	MCP2515_deselect();
	MCP2515_bit_modify(MCP_CANCTRL,0b11100000,MODE_CONFIG);
	MCP2515_bit_modify(MCP_CANCTRL,0b11100000,MODE_LOOPBACK);
	//MCP2515_bit_modify(MCP_CANCTRL,0b11100000,0x00);
}

void MCP2515_write(uint8_t adr, unsigned char data){
	MCP2515_select();
	SPI_send(MCP_WRITE);
	SPI_send(adr);
	SPI_send(data);
	MCP2515_deselect();
}


void MCP2515_read_buffer(unsigned char data){
	MCP2515_select();
	SPI_send(MCP_READ);
	SPI_send(0x00);
	MCP2515_deselect();
}

uint8_t MCP2515_read(uint8_t adr){
	MCP2515_select();
	SPI_send(MCP_READ);
	SPI_send(adr);
	uint8_t received_data = SPI_read();
	MCP2515_deselect();
	return received_data;
}
void MCP2515_reselect(void){
	PORTB |= (1 << PB4);
	PORTB &= ~(1 << PB4);
}

void MCP2515_select(void){
	PORTB &= ~(1 << PB4);
}

void MCP2515_deselect(void){
	PORTB |= (1 << PB4);
}



void MCP2515_request_to_send(uint8_t buffer){
	MCP2515_select();
	switch(buffer){
		case (0):
			SPI_send(MCP_RTS_TX0);
			break;
		case (1):
			SPI_send(MCP_RTS_TX1);
			break;
		case (2):
			SPI_send(MCP_RTS_TX2);
			break;
	}
	MCP2515_deselect();
}

uint8_t MCP2515_read_status(void){
	MCP2515_select();
	SPI_send(MCP_READ_STATUS);
	uint8_t recieved_status = SPI_read();
	MCP2515_deselect();
	return recieved_status;
}

void MCP2515_bit_modify(uint8_t adr, uint8_t mask, uint8_t data){
	MCP2515_select();
	SPI_send(MCP_BITMOD);
	SPI_send(adr);
	SPI_send(mask);
	SPI_send(data);
	MCP2515_deselect();
}
