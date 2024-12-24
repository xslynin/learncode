#include "pwm.h"

void pwm_init(void){
	rGPD0CON &= ~(0xf << 8);
	rGPD0CON |= 0x2 << 8;
	//pclk psys is 66MHZ
	rTCFG0 &= ~(0xff << 8);
	rTCFG0 |= 65 << 8;
	rTCFG0 &= ~(0x0f << 8);
	rTCFG1 |= 1 << 8;

	rTCON |= 1 << 15;
	rTCNTB2 = 250;
	rTCMPB2 = 125;

	rTCON |= 1 << 13;
	//rTCON |= 0 << 13;
	rTCON |= 1 << 12;
}
