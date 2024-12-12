/*
 *  writted by lxs
 *  this file is used for gpio init c file
 *
 */

#include "gpio_init.h"

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
    rKEY_PIN_CON &= ~(0xff << 8);
    //---pull up
    rKEY_PIN_DAT = 0x0;

}
