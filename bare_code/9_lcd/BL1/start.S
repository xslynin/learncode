/*
 * 文件名：	led.s	
 * 作者：	朱老师
 * 描述：	演示重定位（在SRAM内部重定位）
 */

#define WTCON		0xE2700000

#define SVC_STACK	0xd0037d80

.global _start					// 把_start链接属性改为外部，这样其他文件就可以看见_start了
_start:
	ldr r0, =0xE010E81C
	ldr r1, [r0]
	orr r1, r1, #0x300
	orr r1, r1, #0x01
	str r1, [r0]
	
	// 第1步：关看门狗（向WTCON的bit5写入0即可）
	ldr r0, =WTCON
	ldr r1, =0x0
	str r1, [r0]
	
	// 第2步：设置SVC栈
	ldr sp, =SVC_STACK
	
	// 第3步：开/关icache
	mrc p15,0,r0,c1,c0,0;			// 读出cp15的c1到r0中
	//bic r0, r0, #(1<<12)			// bit12 置0  关icache
	orr r0, r0, #(1<<12)			// bit12 置1  开icache
	mcr p15,0,r0,c1,c0,0;

	// 第4步：初始化ddr
	bl sdram_asm_init
	
	// 第5步：重定位	复制
	bl b2_copy_init

@ run_on_dram:			对于第一种分布式加载boot的方案，因为两个bin文件的编译链接是分开执行的，所以长跳转指令将无法照顾到，必须以调用的方式进行跳转
@ 	// 长跳转到led_blink开始第二阶段								等等，好像也不一定，只要两边对应上应该也差不多？我手动的将link lds中的逻辑关系对应即可
@ 	ldr pc, =led_blink				// ldr指令实现长跳转
	
	
// 汇编最后的这个死循环不能丢
	b .
	

	
	
	

	
	
	
	
	
	
	
	
	
