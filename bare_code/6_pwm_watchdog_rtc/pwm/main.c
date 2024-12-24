#include "main.h"
#include "pwm.h"
#include "uart.h"

void delay(unsigned int i){
	while(i--){
        volatile unsigned int j = 10000;
        while(j--);
    }
}

int main(void){
	
	uart_init();
	pwm_init();

	while (1) {
		put('a');
		delay(100);
	}
	return 0;
}