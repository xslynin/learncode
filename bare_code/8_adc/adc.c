#include "adc.h"

void adc_init(void){
	rTSADCCON0 &= ~(1 << 16);	//Resolution select by 10bit
	rTSADCCON0 |= 1 << 14;		//A/D convert prescaler enable

	rTSADCCON0 &= ~(0xFF << 6);		
	rTSADCCON0 |= 65 << 6;			// prescaler - 1, while the pclk is 66MHZ
	
	rTSADCCON0 &= ~(1<<2);			//standby mode off

	rADCMUX &= ~0x0F;
}

void adc_test(void){
	u32 temp = 0;
	rTSADCCON0 |= 0x1;
	//read the state of adc convert
	while(!(rTSADCCON0 & (1 << 15)));
	temp = rTSDATX0 & 0xFFF;
	printf("x: bit14 = %d.\r\n", (rTSDATX0 & (1<<14)));
	printf("axis X is %d \r\n", temp);
	temp = rTSDATY0 & 0xFFF;
	printf("y: bit14 = %d.\r\n", (rTSDATY0 & (1<<14)));
	printf("axis Y is %d \r\n", temp);
}