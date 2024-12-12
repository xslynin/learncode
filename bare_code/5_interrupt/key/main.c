#include "main.h"
#include "gpio_init.h"

void delay(unsigned int i){
	while(i--){
        volatile unsigned int j = 10000;
        while(j--);
    }
}

int main(void){
    gpio_init();
	uart_init();
	while(1){
        //some key is pull
        if ( (~(rKEY_PIN_DAT>>2)) & 0x3){
            delay(1);
            if( (~(rKEY_PIN_DAT>>2)) & 0x1 ){
                rLED_PIN_DAT ^=  0x8;
                put('a');
            }
            else if ( (~(rKEY_PIN_DAT>>2)) & 0x2 ) {
                rLED_PIN_DAT ^= 0x10;
                put('b');
            }
        }
		put('A');
		delay(100);
		//get; receive
		//get();
	}
	
	return 0;
}
