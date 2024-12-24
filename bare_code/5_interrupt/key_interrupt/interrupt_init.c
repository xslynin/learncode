#include "interrupt_init.h"
#include "uart.h"
extern void IRQ_handle(void);
//extern unsigned int IRQ_handle;
// void reset_exception(void)
// {
// 	put('1');
// }

// void undef_exception(void)
// {
// 	put('2');
// }

// void sotf_int_exception(void)
// {
// 	put('3');
// }

// void prefetch_exception(void)
// {
// 	put('4');
// }

// void data_exception(void)
// {
// 	put('5');
// }


void sys_interrupt_init(void){
//     r_execpt_reset    = (unsigned int)reset_exception;
//     r_execpt_undef    = (unsigned int)undef_exception;
//    // r_execpt_soft_int = (unsigned int)sotf_int_exception;
//     r_execpt_prefetch = (unsigned int)prefetch_exception;
//     r_execpt_data     = (unsigned int)data_exception;
    r_execpt_irq      = (unsigned int)IRQ_handle;
    r_execpt_fiq      = (unsigned int)IRQ_handle;

    //disable all the interrupt for initiation
    VIC0INTENCLEAR = 0xFFFFFFFF;
    VIC1INTENCLEAR = 0xFFFFFFFF;
    VIC2INTENCLEAR = 0xFFFFFFFF;
    VIC3INTENCLEAR = 0xFFFFFFFF;

    //select irq for interrupt request
    VIC0INTSELECT = 0x0;
    VIC1INTSELECT = 0x0;
    VIC2INTSELECT = 0x0;
    VIC3INTSELECT = 0x0;

    clear_vic_addr();
}

void clear_vic_addr(void){
    //clear the previous isr
    VIC0ADDR = 0;
    VIC1ADDR = 0;
    VIC2ADDR = 0;
    VIC3ADDR = 0;
}

void interrupt_enable(unsigned long inum){
    unsigned long temp;
    if(inum < 32){
        temp = VIC0INTENABLE;
        temp |= (1 << inum);
        VIC0INTENABLE = temp;
    }
    else if(inum < 64){
        temp = VIC1INTENABLE;
        temp |= (1 << (inum - 32));
        VIC1INTENABLE = temp;
    }
    else if(inum < 96){
        temp = VIC2INTENABLE;
        temp |= (1 << (inum - 64));
        VIC2INTENABLE = temp;
    }
    else if(inum < NUM_ALL){
        temp = VIC3INTENABLE;
        temp |= (1 << (inum - 96));
        VIC3INTENABLE = temp;
    }
    //when inume more than all the vic, easily enable all the enable
    else {
        VIC0INTENABLE = 0xFFFFFFFF;
        VIC1INTENABLE = 0xFFFFFFFF;
        VIC2INTENABLE = 0xFFFFFFFF;
        VIC3INTENABLE = 0xFFFFFFFF;
    }
}

void interrupt_disable(unsigned long inum){
    unsigned long temp;
    if(inum < 32){
        temp = VIC0INTENCLEAR;
        temp |= (1 << inum);
        VIC0INTENCLEAR = temp;
    }
    else if(inum < 64){
        temp = VIC1INTENCLEAR;
        temp |= (1 << (inum - 32));
        VIC1INTENCLEAR = temp;
    }
    else if(inum < 96){
        temp = VIC2INTENCLEAR;
        temp |= (1 << (inum - 64));
        VIC2INTENCLEAR = temp;
    }
    else if(inum < NUM_ALL){
        temp = VIC3INTENCLEAR;
        temp |= (1 << (inum - 96));
        VIC3INTENCLEAR = temp;
    }
    //when inume more than all the vic, easily disable all the enable
    else {
        VIC0INTENCLEAR = 0xFFFFFFFF;
        VIC1INTENCLEAR = 0xFFFFFFFF;
        VIC2INTENCLEAR = 0xFFFFFFFF;
        VIC3INTENCLEAR = 0xFFFFFFFF;
    }
}

void interrupt_bind_isr2vectoraddr(unsigned long inum, void (*handler)(void)){
    //VIC0
    if(inum<32){
        *( (volatile unsigned long *)(VIC0VECTADDR + 4*(inum-0)) ) = (unsigned)handler;
    }
    //VIC1
    else if(inum<64){
        *( (volatile unsigned long *)(VIC1VECTADDR + 4*(inum-32)) ) = (unsigned)handler;
    }
    //VIC2
    else if(inum<96){
        *( (volatile unsigned long *)(VIC2VECTADDR + 4*(inum-64)) ) = (unsigned)handler;
    }
    //VIC3
    else{
        *( (volatile unsigned long *)(VIC3VECTADDR + 4*(inum-96)) ) = (unsigned)handler;
    }
    return;
}

//get known that which vic is active
unsigned long intc_getvicirqstatus(unsigned long ucontroller){
    if(ucontroller == 0)
        return	VIC0IRQSTATUS;
    else if(ucontroller == 1)
        return 	VIC1IRQSTATUS;
    else if(ucontroller == 2)
        return 	VIC2IRQSTATUS;
    else if(ucontroller == 3)
        return 	VIC3IRQSTATUS;
    else;
    return 0;
}

void none_use_function(void){
    return;
}

void irq_handler(void){
    //do something
    unsigned long vicnaddr_current[4] = {VIC0ADDR,VIC1ADDR,VIC2ADDR,VIC3ADDR};
    int i ;
    void (* isr)(void) = NULL;
    for (i = 0; i < 4; i++) {
        if(intc_getvicirqstatus(i)){
            isr = (void (*)(void))vicnaddr_current[i];
        } 
    }
    (* isr)();
}
