/*
 * Oving1_TTK4155_G17_H17.c
 *
 * Created: 04.09.2017 11:50:29
 *  Author: pamarton
 */ 
#include <stdio.h>
#define VERSION "l4d2"
#define F_CPU 4915200 // clock frequency in Hz
#define BAUDRATE 9600 // Valgt verdi data sendt pr sekund
#define UBBR 32 - 1 //F_CPU/(16*BAUDRATE)-1 //USART BAUD RATE REGISTER VALUE
#include "adc.h"
#include <avr/io.h>

#define UNDERLINE 0b10000000
#define STREAKTROUGH 0b00010000
#define CENCORED 0b11111111

//#include <avr/interrupt.h>
#include "uart.h"
#include "i_o.h"
#include "input_conversion.h"
#include "button_interrupts.h"

#define MAX_SIGNAL 0xFF
#define MIN_SIGNAL 0
void SRAM_test(void);
void initalize(void);
void bootscreen(void);
#include "oled.h"
#include "menu.h"
#include "SPI.h"



int main(void)
{
	
	initalize();
	
	sram_init();
	oled_goto_line(7);
	//sram_write_string(" - BYGGERN - G17");
	
	
	cli();
	SPI_initialize();
	int i = SPI_read_instruction(0b00010000);
	printf("%i",i);
	
	char test = 0xff;
	if(test > 0xfff){
		printf("ASDASF");
	}
	while (1)
	{
		int i = SPI_read_instruction(0b00000000);
		_delay_ms(10);
		printf("%i",i);
	}
	printf("\n\n\n\n\n");
	write_screen();
	int d = 0;
	while(1){
		
		
		//_delay_ms(100);
		oled_goto_line(5);
		//sram_write_char(SPI_read());
		oled_goto_line(6);
		sram_write_string("DONE");
		//_delay_ms(100);
		write_screen();
		d++;
	}
	
	
	
	while(1){
		_delay_ms(20);
		menu_update();
	}
	
	//testUart();
	
}






void initalize(void){
	cli();//disable interrupts
	init_UART(UBBR);
	printf("LOADING g17_%s %s %s\nINITIALIZING...\n\nUART successfully initialized\n\n", VERSION,__DATE__,__TIME__);
	BIT_ON(MCUCR,SRE); //SET THIS IN SOME INITALIZE FUNBCTION
	BIT_ON(SFIOR,XMM2);//HVORFOR GJORDE DE DETTE I OLED?
	
	oled_ini();
	sram_init();
	//bootscreen();
	write_screen();
	
	
	printf("OLED successfully initialized\n");
	initialize_menu();
	
	initialize_control_input();
	printf("control input successfully initialized\n\n");
	SRAM_test();
	printf("SRAM successfully initialized\n");
	initalize_interrupts();
	printf("Interrupts successfully initialized\n");
	printf("Interrupts activated\n");
	printf("\nINITIALIZATION COMPLETE\n");
	sei();//enable interrupts
}

#include <stdlib.h>
void SRAM_test(void)//CAN BE REMOVED, IN CASE OF LOW STORAGE
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i,	retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the writephase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n",i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with\n%4d errors in write phase and\n%4d errors	in retrieval phase\n\n", write_errors, retrieval_errors);
}



void bootscreen(void){
	int x = 24;
	int y = 61;
	sram_draw_line(x,y,x-15,y-60);//letter G
	sram_draw_line(x-15,y-60,x+15,y-60);
	sram_draw_line(x+15,y-60,x+12,y-48);
	sram_draw_line(x+12,y-48,x-6,y-48);
	sram_draw_line(x-6,y-48,x,y-24);
	sram_draw_line(x,y-24,x+3,y-36);
	sram_draw_line(x+3,y-36,x+9,y-36);
	sram_draw_line(x+9,y-36,x,y);//end of letter
	
	
	
	x += 40;
	sram_draw_rectangle(x-5,y,x+5,y-60);//number 1, end of number
	//sram_draw_triangle(x-7,y-60,x+7,y-60,x,y-30);//1
	//sram_draw_triangle(x-7,y,x+7,y,x,y-30);//1
	
	x += 40;
	
	sram_draw_line(x,y,x+15,y-60);//number 7
	sram_draw_line(x-15,y-60,x+15,y-60);
	sram_draw_line(x-15,y-60,x-12,y-48);
	sram_draw_line(x-12,y-48,x+6,y-48);
	sram_draw_line(x+6,y-48,x+3,y-36);
	sram_draw_line(x+3,y-36,x-9,y-36);
	sram_draw_line(x-9,y-36,x-6,y-24);
	sram_draw_line(x-6,y-24,x,y-24);
	sram_draw_line(x,y-24,x-3,y-12);
	sram_draw_line(x-3,y-12,x,y);//end of number
	
}