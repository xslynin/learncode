#if 1
#endif
#include "main.h"
void delay(void){
	volatile unsigned int i = 900000;
	while(i--);
}

int main(void){
	uart_init();
	while(1){
		//put; transmit 
		put('A');
		delay();
		//get; receive
		//get();
	}
	
	return 0;
}
