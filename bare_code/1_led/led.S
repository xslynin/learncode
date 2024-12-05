//this is first assembly program
.global _start

_start:
	//first, configure the register
	ldr r0, =0x00111000			//set GPJ0CON controlling the pin to output
	ldr r1, =0xE0200240			//get the register
	str r0, [r1]				//write the register
init:
	ldr r0, =0b11011111
	ldr r1, =0xE0200244
	ldr r4, =0x1
	str r0, [r1]

blink: 
	bl delay
	mov r5, r0, asr r4
	str r5, [r1]
	add r4, r4, #0x1
	cmp r4, #3
	ldreq r4, =0x0
	b blink	

delay:
	ldr r2, =0xFFFFFF
	ldr r3, =0x0
delay_loop:
	sub r2, r2, #1
	cmp r2, r3	
	bne delay_loop
	mov pc, lr
