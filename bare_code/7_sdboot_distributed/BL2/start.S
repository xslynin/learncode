.global _start					// 把_start链接属性改为外部，这样其他文件就可以看见_start了
_start:
	// 长跳转到led_blink开始第二阶段
	ldr pc, =main				// ldr指令实现长跳转
	
// 汇编最后的这个死循环不能丢
	b .
	

	
	
	

	
	
	
	
	
	
	
	
	
