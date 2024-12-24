/*
 *  writted by lxs
 *  this file is used for gpio init c file
 *
 */

#include "gpio_init.h"
#include "interrupt_init.h"
#include "uart.h"
 //in these assignment, we need to configure the gpio of key and led
void gpio_init(void){
    //lets configure the led pin for output!
    unsigned int temp = 0;
    temp = rLED_PIN_CON & (~(0xff << 12));
    rLED_PIN_CON |= 0x11 << 12;
    //---pull up
    rLED_PIN_DAT = 0x18;
    //rLED_PIN_DAT = 0x0;
    //rLED_PIN_PUD = 0xa << 6;
    //lets configure the key pin for input first and then try the interrupt
    //ok now we try key for init
   
    //---pull up
    //rKEY_PIN_DAT = 0x0;
}

void key_interrupt_init_enable1(void){
     rKEY_PIN_CON |= 0xFF << 8;
    rKEY_EINT_CON &= ~(0xFF << 8);
    rKEY_EINT_CON |= ((2<<8)|(2<<12));
    rKEY_EINT_MASK &= ~ (3<<2);
    rKEY_EINT_PEND |= (3<<2);    //clear the current bit and reserver the other bit 
}

void gpio_toggle_key1(void){
    rLED_PIN_DAT ^=  0x8;
    put('a');
    rKEY_EINT_PEND |= 0x4;
    clear_vic_addr();
}

void gpio_toggle_key2(void){
    rLED_PIN_DAT ^= 0x10;
    put('b');
    rKEY_EINT_PEND |= 0x8;
    clear_vic_addr();
}