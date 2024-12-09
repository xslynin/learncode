#define GPJ0CON 0xE0200240
#define GPJ0DAT 0xE0200244

//use C for accessing the register means access the corresponse address
void delay(void){
	volatile unsigned int i = 900000;
	//volatile escape the optical behavior of compiler
	while(i--);
}

void led_blink(void){
	//init
	unsigned int * p = (unsigned int *)GPJ0CON;
	*p = 0x11111111;
	p = (unsigned int *)GPJ0DAT; 
	//main execute
	while(1){
		*p = 0x00;
		delay();
		*p = (1 << 3) | (1 << 4) | (1 << 5);
		delay();
	}
}	
