/*
 * SPI.h
 *
 * Created: 10.10.2017 17:15:55
 *  Author: pamarton
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include "uart.h" //REMOVE AFTER USE
#include "i_o.h"

void SPI_write_instruction(uint8_t reg, unsigned char data);
void SPI_read_buffer(unsigned char data);
void SPI_initialize(void);

void SPI_select(void);
void SPI_deselect(void);
void SPI_reselect(void);

void SPI_send(char data);
char SPI_read(void);

#endif /* SPI_H_ */