#include "s5pv210.h"

#define set_pll(m,p,s)	(1<<31 | m<<16 | p<<8 | s)
#define APLL_VAL	set_pll(125,3,1)
#define MPLL_VAL	set_pll(667,12,1)
.global clock_init

clock_init:
	//first do not use pll
	ldr r0, =ELFIN_CLOCK_POWER_BASE
	ldr r1, =0x0
	str r1, [r0, #CLK_SRC0_OFFSET]
	//second set pll lock time
	ldr r1, =0x000002CF  //pref = source_clock / PDIV for standard 1000MHZ, PDIV should be 3 , the source is 24MHZ, and based on pref = 8MHZ, the lock time should less than 30us, so the counter should less than 720
	str r1, [r0, #APLL_LOCK_OFFSET]
	ldr r1, =0x12C0		//667MHZ for MPLL, 200us count for 24MHZ / 12 PDIV
	str r1, [r0, #MPLL_LOCK_OFFSET]
	//thirdly set div  
	ldr r1, =0x14131440
	str r1, [r0, #CLK_DIV0_OFFSET]
	//fourthly set pll multi frequency
	ldr r1, =APLL_VAL
	str r1, [r0, #APLL_CON0_OFFSET]
	ldr r1, =MPLL_VAL
	str r1, [r0, #MPLL_CON_OFFSET]
	//fivethly set mux open (mask) and so on
	ldr r1, [r0, #CLK_SRC0_OFFSET]
	ldr r2, =0x10000011
	orr r1, r1, r2
	str r1, [r0, #CLK_SRC0_OFFSET]

	mov pc, lr	
