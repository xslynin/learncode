/*
*   Writted by lxs
*   this file is used for the gpio init header
*
*/


#ifndef _GPIOINIT_H
#define _GPIOINIT_H
#include "s5pv210.h"

//easy way to point the register value
#define reg_depoint(base,offset)      *(volatile unsigned int*)(base+offset)
//------------CON--------------------------------------------------------------------------------------//
//led 1 2  in gpj0_3 4 
#define rLED_PIN_CON    reg_depoint(ELFIN_GPIO_BASE,GPJ0CON_OFFSET)
//left key sw5 and down key sw6 for gph0_2 3   
#define rKEY_PIN_CON   reg_depoint(ELFIN_GPIO_BASE,GPH0CON_OFFSET)

//------------DAT--------------------------------------------------------------------------------------//
//led 1 2 3 in gpj0_3 4
#define rLED_PIN_DAT    reg_depoint(ELFIN_GPIO_BASE,GPJ0DAT_OFFSET)
//left key sw5 and down key sw6 for gph0_2 3
#define rKEY_PIN_DAT   reg_depoint(ELFIN_GPIO_BASE,GPH0DAT_OFFSET)


//------------PUD--------------------------------------------------------------------------------------//
//led 1 2 3 in gpj0_3 4 5 
#define rLED_PIN_PUD    reg_depoint(ELFIN_GPIO_BASE,GPJ0PUD_OFFSET)
//left key sw5 and down key sw6 for gph0_2 3  
#define rKEY_PIN_PUD   reg_depoint(ELFIN_GPIO_BASE,GPH0PUD_OFFSET)

void gpio_init(void);

#endif