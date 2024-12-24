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
    
}

int main(void){
    gpio_init();
    uart_init();
    key_interrupt_init_enable1();
    
    sys_interrupt_init();

    //bind isr(in reg) for response handle function(by user)
    interrupt_bind_isr2vectoraddr(NUM_EINT2, gpio_toggle_key1);
    interrupt_bind_isr2vectoraddr(NUM_EINT3, gpio_toggle_key2);

    //allow the eint2 eint3 for key interrupt
    interrupt_enable(NUM_EINT2);
    interrupt_enable(NUM_EINT3);
	while(1){
		put('A');
		delay(100);
		//get; receive
		//get();
	}
	
	return 0;
}
