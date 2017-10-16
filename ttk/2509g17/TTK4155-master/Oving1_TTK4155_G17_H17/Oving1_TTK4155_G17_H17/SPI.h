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
#include "MCP2515.h"

void SPI_initialize(void);
void SPI_send(char data);
char SPI_read(void);
void SPI_select(void);
void SPI_deselect(void);

#endif /* SPI_H_ */