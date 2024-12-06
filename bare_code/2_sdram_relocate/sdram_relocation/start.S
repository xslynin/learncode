//this is first assembly program
.global _start

_start:
	//turn off the watch dog	
	ldr r0, =0x00
	ldr r1, =0xE2700000
	str r0, [r1]

	ldr sp, =0xD0037D80			//set svc stack and then we could use C progam, and set the high address in svc stack image for down growing stack

	mrc p15, 0, r0, c1, c0, 0	//coprocesser
//	bic r0, r0, #(1<<12)		//op1  &  ~op2  close icache
	orr r0, r0, #(1<<12)		//	   |		turn on
	mcr p15, 0, r0, c1, c0, 0

	// relocated
	adr r0, _start
	ldr r1, =_start
	ldr r2, =bss_start
	cmp r0, r1
	beq bss_clean
	
relocate_loop:
	ldr r3, [r0], #4 // source and self-add
	str r3, [r1], #4 // target and self-add 
	cmp r0, r2
	bne relocate_loop
	
	//bss clean
bss_clean:
	//r2 has been defined the bss_start
	ldr r1, =bss_end   		//these two variable come from the link script
	cmp r2, r1
	beq dram_jump
	mov r0, #0
clean_loop:
	str r0, [r1], #4
	cmp r1, r2
	bne clean_loop

	//dram long jump
dram_jump:
	ldr pc, =led_blink
	
/*
*
*
*
*
*
*/
	bl led_blink
// Couldn't lack the dead loop
	b .
