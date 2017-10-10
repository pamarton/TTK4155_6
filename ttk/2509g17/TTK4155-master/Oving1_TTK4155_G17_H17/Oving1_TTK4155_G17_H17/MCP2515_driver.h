/*
 * MCP2515_driver.h
 *
 * Created: 10.10.2017 18:09:00
 *  Author: pamarton
 */ 


#ifndef MCP2515_DRIVER_H_
#define MCP2515_DRIVER_H_

#include "SPI.h"

void MCP2515_write(uint8_t adr, unsigned char data);
void MCP2515_read_buffer(unsigned char data);
uint8_t MCP2515_read(uint8_t adr);

void MCP2515_select(void);
void MCP2515_deselect(void);
void MCP2515_reselect(void);

void MCP2515_request_to_send(uint8_t buffer);

void MCP2515_initialize(void);

void MCP2515_bit_modify(uint8_t adr, uint8_t mask, uint8_t data);


#endif /* MCP2515_DRIVER_H_ */

