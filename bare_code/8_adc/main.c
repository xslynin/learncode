#include "main.h"
#include "adc.h"
// #include "gpio_init.h"
// #include "interrupt_init.h"

void delay(unsigned int i){
	while(i--){
        volatile unsigned int j = 10000;
        while(j--);
    }
}

void key_interrupt_init_enable2(void){
    
}

int main(void){
    uart_init();
	adc_init();
	u32 value = 0;

	while(1){
		adc_test();
		delay(1000);
		
	}
	
	return 0;
}
