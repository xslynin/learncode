/*
 *writed by lxs
 *uart 
 *
 *
 */
#include "uart.h"
#if 1 
#define uart0_pin_mask 0x00000022

#define	rGPA0CON (*(volatile unsigned int *)ELFIN_GPIO_BASE)
#define rULCON0 (*(volatile unsigned int *)ELFIN_UART_CONSOLE_BASE)
#define rUCON0 (*(volatile unsigned int *)(ELFIN_UART_CONSOLE_BASE + UCON_OFFSET))
#define rUFCON0 (*(volatile unsigned int *)(ELFIN_UART_CONSOLE_BASE + UFCON_OFFSET))
#define rUMCON0 (*(volatile unsigned int *)(ELFIN_UART_CONSOLE_BASE + UMCON_OFFSET))

#define rUBRDIV0 (*(volatile unsigned int *)(ELFIN_UART_CONSOLE_BASE + UBRDIV_OFFSET))
#define rUDIVSLOT0 (*(volatile unsigned int *)(ELFIN_UART_CONSOLE_BASE + UDIVSLOT_OFFSET))

#define rUTRSTAT0 (*(volatile unsigned int *)(ELFIN_UART_CONSOLE_BASE + UTRSTAT_OFFSET))

#define rUTXH0 (*(volatile unsigned int *)(ELFIN_UART_CONSOLE_BASE + UTXH_OFFSET))
#define rURXH0 (*(volatile unsigned int *)(ELFIN_UART_CONSOLE_BASE + URXH_OFFSET))
#endif

void uart_init(void){
	//config register, baud rate and so on
	//1. configure the base register about the uart
	rGPA0CON &= ~(0xff << 0);
	rGPA0CON |= uart0_pin_mask;
	//use PCLK, and uart belong to psys domain, the value is 66.7MHZ
	rULCON0 = 0x3;
	rUCON0 = 0x5;
	rUFCON0 = 0x0;
	rUMCON0 = 0x0;
	//2. configure the baud rate related registers
	rUBRDIV0 = 35;
	rUDIVSLOT0 = 0x0888;
}

//uart transmit
void put(char word){
	//send a word
	while(!(rUTRSTAT0 &(1 << 1)));
	rUTXH0 = word << 0;
}

char get(void){
	//get a word
	while(!(rUTRSTAT0 & (1 << 0)));
	return rURXH0 & 0xff;
}
