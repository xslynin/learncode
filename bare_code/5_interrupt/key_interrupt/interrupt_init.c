#include "interrupt_init.h"

void sys_interrupt_init(void){
    r_execpt_reset    = (unsigned int)none_use_function;
    r_execpt_undef    = (unsigned int)none_use_function;
    r_execpt_prefetch = (unsigned int)none_use_function;
    r_execpt_data     = (unsigned int)none_use_function;
    r_execpt_irq      = (unsigned int)irq_handler;
    r_execpt_fiq      = (unsigned int)none_use_function;

    //disable all the interrupt for initiation
    VIC0INTENCLEAR = 0xffffffff;
    VIC1INTENCLEAR = 0xffffffff;
    VIC2INTENCLEAR = 0xffffffff;
    VIC3INTENCLEAR = 0xffffffff;

    //select irq for interrupt request
    VIC0INTSELECT = 0x0;
    VIC1INTSELECT = 0x0;
    VIC2INTSELECT = 0x0;
    VIC3INTSELECT = 0x0;

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
        temp = VIC0INTENABLE;
        temp |= (1 << (inum - 32));
        VIC1INTENABLE = temp;
    }
    else if(inum < 96){
        temp = VIC0INTENABLE;
        temp |= (1 << (inum - 64));
        VIC2INTENABLE = temp;
    }
    else if(inum < NUM_ALL){
        temp = VIC0INTENABLE;
        temp |= (1 << (inum - 96));
        VIC3INTENABLE = temp;
    }
    //when inume more than all the vic, easily enable all the enable
    else {
        VIC0INTENABLE = 0xffffffff;
        VIC1INTENABLE = 0xffffffff;
        VIC2INTENABLE = 0xffffffff;
        VIC3INTENABLE = 0xffffffff;
    }
}

void interrupt_disable(unsigned long inum){
    unsigned long temp;
    if(inum < 32){
        temp = VIC0INTENABLE;
        temp |= (1 << inum);
        VIC0INTENABLE = temp;
    }
    else if(inum < 64){
        temp = VIC0INTENABLE;
        temp |= (1 << (inum - 32));
        VIC1INTENABLE = temp;
    }
    else if(inum < 96){
        temp = VIC0INTENABLE;
        temp |= (1 << (inum - 64));
        VIC2INTENABLE = temp;
    }
    else if(inum < NUM_ALL){
        temp = VIC0INTENABLE;
        temp |= (1 << (inum - 96));
        VIC3INTENABLE = temp;
    }
    //when inume more than all the vic, easily disable all the enable
    else {
        VIC0INTENCLEAR = 0xffffffff;
        VIC1INTENCLEAR = 0xffffffff;
        VIC2INTENCLEAR = 0xffffffff;
        VIC3INTENCLEAR = 0xffffffff;
    }
}

void interrupt_bind_isr2vectoraddr(unsigned long inum, void (*handler)(void)){
    //VIC0
    if(inum<32){
        *( (volatile unsigned long *)(VIC0VECTADDR + 4*(intnum-0)) ) = (unsigned long)handler;
    }
    //VIC1
    else if(inum<64){
        *( (volatile unsigned long *)(VIC1VECTADDR + 4*(intnum-32)) ) = (unsigned long)handler;
    }
    //VIC2
    else if(inum<96){
        *( (volatile unsigned long *)(VIC2VECTADDR + 4*(intnum-64)) ) = (unsigned long)handler;
    }
    //VIC3
    else{
        *( (volatile unsigned long *)(VIC3VECTADDR + 4*(intnum-96)) ) = (unsigned long)handler;
    }
    return;
}

//get known that which vic is active
static unsigned long intc_getvicirqstatus(unsigned long ucontroller){
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
    int i = 0;
    void (* isr)(void) = NULL;

    for (i; i < 4; i++) {
        if(intc_getvicirqstatus(i))
            isr = (void (*)(void))vicnaddr_current[i];
    }
    (* isr)();
}
