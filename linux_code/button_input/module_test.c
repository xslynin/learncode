#include <linux/input.h>
#include <linux/module.h>
#include <linux/init.h>

#include <asm/irq.h>
#include <asm/io.h>

#include <mach/irqs.h>
#include <linux/interrupt.h>
#include <mach/gpio.h>
#include <linux/delay.h>

#define BUTTON_IRQ IRQ_EINT2

static struct input_dev *button_dev;

static void func(unsigned long data){
	int flag;
	printk(KERN_ERR "this is bottom half happened");
	//when handle the interrupt, the gpio mode should be set to input
	s3c_gpio_cfgpin(S5PV210_GPH0(2), S3C_GPIO_SFN(0X0));
	//then read and recovery
	udelay(1);
	flag = gpio_get_value(S5PV210_GPH0(2));
	s3c_gpio_cfgpin(S5PV210_GPH0(2), S3C_GPIO_SFN(0X0F));

	//could be used as the top half interrupt
	input_report_key(button_dev, KEY_LEFT, !flag);
	input_sync(button_dev);

}

DECLARE_TASKLET(mytasklet, func, 0);

static irqreturn_t button_interrupt(int irq, void *dummy)
{
	printk(KERN_ERR "this is top half happened case ! \n");
	tasklet_schedule(&mytasklet);
	return IRQ_HANDLED;
}

static int __init button_init(void)
{
	int error;

	//in initialization, require the gpio
	error = gpio_request(S5PV210_GPH0(2), "GPH0_2");
	if(error){
		printk(KERN_ERR "GPIO request failed!\n");
		goto next;
	}
	//config the gpio mode
	s3c_gpio_cfgpin(S5PV210_GPH0(2), S3C_GPIO_SFN(0X0F));

next:
	if (request_irq(BUTTON_IRQ, button_interrupt, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "button", NULL)) {
                printk(KERN_ERR "button: Can't allocate irq %d\n", BUTTON_IRQ);
                return -EBUSY;
        }

	button_dev = input_allocate_device();
	if (!button_dev) {
		printk(KERN_ERR "button: Not enough memory\n");
		error = -ENOMEM;
		goto err_free_irq;
	}

	button_dev->evbit[0] = BIT_MASK(EV_KEY);
	button_dev->keybit[BIT_WORD(KEY_LEFT)] = BIT_MASK(KEY_LEFT);

	error = input_register_device(button_dev);
	if (error) {
		printk(KERN_ERR "button: Failed to register device\n");
		goto err_free_dev;
	}

	return 0;

 err_free_dev:
	input_free_device(button_dev);
 err_free_irq:
	free_irq(BUTTON_IRQ, button_interrupt);
	return error;
}

static void __exit button_exit(void)
{
	gpio_free(S5PV210_GPH0(2));
    input_unregister_device(button_dev);
	free_irq(BUTTON_IRQ, button_interrupt);
}

module_init(button_init);
module_exit(button_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("lxs");
MODULE_DESCRIPTION("x210 led driver");


