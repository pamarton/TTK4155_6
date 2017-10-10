/*
 * SPI.c
 *
 * Created: 10.10.2017 17:15:47
 *  Author: pamarton
 */ 
#include "SPI.h"


void SPI_write_instruction(uint8_t reg, unsigned char data){
	
}


void SPI_read_buffer(unsigned char data){
	SPI_select();
	SPI_send(0b00000011);
	SPI_send(0b11111111);
	SPI_deselect();
}

unsigned int SPI_read_instruction(char adr){
	SPI_select();
	SPI_send(0b00000011);
	SPI_send(adr);
	unsigned int received_data = SPI_read();
	SPI_deselect();
	return received_data;
}

void SPI_initialize(void){
	DDRB |=	(1 << PB5) | (1 << PB7) | (1 << PB4);
	DDRB &= ~(1 << PB6);
	PORTB |= (1 << PB4);
	//BIT_ON(SPCR,SPIE);		//SPI INTERRUPT ENABLE
	//BIT_OFF(SPCR,DORD);		//transmit the most significant bit first, change to ON if we transmit the Least significant first
	BIT_ON(SPCR,MSTR);		//MASTER/SLAVE SELECT, set to 1 for master, 0 for slave (master wanted)
	//BIT_ON(SPCR,CPOL);		//CLOCK POLARITY, NO IDEA WHAT WE NEED!!!!!!!!!!!!!
	//BIT_ON(SPCR,CPHA);		//CLOCK PHASE, NO IDEA!!!!!!!!!!!
	//BIT_ON(SPCR,SPR1);		//SPI CLOCK RATE SELECT, BIT 1
	//BIT_ON(SPCR,SPR0);		//SPI CLOCK RATE SELECT, BIT 0
	BIT_ON(SPCR,SPE);		//SPI ENABLE, overrides the normal pins function (we want this)
	//sei();
	SPI_deselect();
}

void SPI_reselect(void){
	PORTB |= (1 << PB4);
	PORTB &= ~(1 << PB4);
}

void SPI_select(void){
	PORTB &= ~(1 << PB4);
}

void SPI_deselect(void){
	PORTB |= (1 << PB4);
}


void SPI_send(char data) {
	//Start the transmission
	SPDR = data;
	
	//Wait for data to be transmitted (checks if the register is empty)
	while(!(SPSR & (1<<SPIF)));
}



char SPI_read(void){
	//Send dummy data to read from slave
	SPI_send(0);
	
	//Wait for data to be received
	while(!(SPSR & (1<<SPIF)));

	return SPDR;
}

