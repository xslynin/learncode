#include "main.h"
#include "gpio_init.h"
#include "interrupt_init.h"

void delay(unsigned int i){
	while(i--){
        volatile unsigned int j = 10000;
        while(j--);
    }
}

void key_interrupt_init_enable2(void){
    //bind isr(in reg) for response handle function(by user)
    interrupt_bind_isr2vectoraddr(NUM_EINT2, gpio_toggle_key1());
    interrupt_bind_isr2vectoraddr(NUM_EINT3, gpio_toggle_key2());

    //allow the eint2 eint3 for key interrupt
    interrupt_enable(NUM_EINT2);
    interrupt_enable(NUM_EINT3);
}

int main(void){
    sys_interrupt_init();
    gpio_init();
    key_interrupt_init_enable2();
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
