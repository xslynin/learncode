//this is first assembly program
.global _start

_start:
	//turn off the watch dog	
	ldr r0, =0x00
	ldr r1, =0xE2700000
	str r0, [r1]

	ldr sp, =0xD0037D80			//set svc stack and then we could use C progam, and set the high address in svc stack image for down growing stack
	bl led_blink
// Couldn't lack the dead loop
	b .
