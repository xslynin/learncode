//this is first assembly program
.global _start

_start:
	//turn off the watch dog	
	ldr r0, =0x00
	ldr r1, =0xE2700000
	str r0, [r1]

	ldr sp, =0xD0037D80			//set svc stack and then we could use C progam, and set the high address in svc stack image for down growing stack

	mrc p15, 0, r0, c1, c0, 0	//coprocesser
	bic r0, r0, #(1<<12)		//op1  &  ~op2
	orr r0, r0, #(1<<12)		//	   |
	mcr p15, 0, r0, c1, c0, 0


	bl led_blink
// Couldn't lack the dead loop
	b .
