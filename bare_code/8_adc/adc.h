#ifndef _ADC_H
#define _ADC_H

#include "s5pv210.h"
#include "lib/printf.h"

#define rTSADCCON0		reg_depoint(ELFIN_ADC_BASE,0x00)		
#define rTSDLY0			reg_depoint(ELFIN_ADC_BASE,0x08)
#define rTSDATX0		reg_depoint(ELFIN_ADC_BASE,0x0C)
#define rTSDATY0		reg_depoint(ELFIN_ADC_BASE,0x10)
#define rTSPENSTAT0		reg_depoint(ELFIN_ADC_BASE,0x14)
#define rCLRINTADC0		reg_depoint(ELFIN_ADC_BASE,0x18)
#define rADCMUX			reg_depoint(ELFIN_ADC_BASE,0x1C)
#define rCLRINTPEN0		reg_depoint(ELFIN_ADC_BASE,0x20)

void adc_init(void);
void adc_test(void);

#endif