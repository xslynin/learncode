#define SVC_STACK 0xD0037D80
#define IRQ_STACK 0xD0037F80
//this is first assembly program
.global _start
.global IRQ_handle

_start:
	//turn off the watch dog	
	ldr r0, =0x00
	ldr r1, =0xE2700000
	str r0, [r1]

	bl clock_init

	ldr sp, =SVC_STACK			//set svc stack and then we could use C progam, and set the high address in svc stack image for down growing stack

	mrc p15, 0, r0, c1, c0, 0	//coprocesser
//	bic r0, r0, #(1<<12)		//op1  &  ~op2  close icache
	orr r0, r0, #(1<<12)		//	   |		turn on
	mcr p15, 0, r0, c1, c0, 0

	bl main
// Couldn't lack the dead loop
	b .

@ IRQ_handle:
@     //set the stack of irq mode
@     ldr sp, =IRQ_STACK
@     //save lr, 
@     sub lr, lr, #4
@     stmfd sp!, {r0-r12, lr}
@     bl irq_handler
@     ldmfd sp!, {r0-r12, pc}^