#ifndef _PWM_H
#define _PWM_H

#include "s5pv210.h"

#define rGPD0CON	reg_depoint(ELFIN_GPIO_BASE,GPD0CON_OFFSET)
#define rTCFG0		reg_depoint(0xE2500000,0)
#define rTCFG1 		reg_depoint(0xE2500004,0)
#define rTCON 		reg_depoint(0xE2500008,0)
#define rTCNTB2 	reg_depoint(0xE2500024,0)
#define rTCMPB2		reg_depoint(0xE2500028,0)

void pwm_init(void);
#endif