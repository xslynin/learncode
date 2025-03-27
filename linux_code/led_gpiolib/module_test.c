/*
 *	In this file, register led gpio by another way , that is , register it in sys/class	
 *	
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/leds.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <mach/gpio.h>


#define LED1_gpio S5PV210_GPJ0(3) 	
#define LED2_gpio S5PV210_GPJ0(4)
#define LED3_gpio S5PV210_GPJ0(5)
#define log_on		0
#define log_off		1
#define LED_OFF		0


static struct led_classdev x210_led;

static void x210_led_set(struct led_classdev *led_cdev, enum led_brightness value){
	//turn on the led
	if(value != LED_OFF){
		printk(KERN_INFO "turn on the led\n");
		gpio_set_value(LED1_gpio, log_on);
//		writel(((0<<3)|(0<<4)|(0<<5)), S5PV210_GPJ0DAT);
	}else{//close the led
		printk(KERN_INFO "turn off the led\n");
		gpio_set_value(LED1_gpio, log_off);
//		writel(((1<<3)|(1<<4)|(1<<5)), S5PV210_GPJ0DAT);
	}

}

static void x210_led_array_init(struct led_classdev * plc){
	plc->name = "led1";
	plc->brightness = 0;
	plc->brightness_set = x210_led_set;
}

static int __init x210led_init(void){
	int ret;
	ret = -1;

	if(gpio_request(LED1_gpio, "test")){
		printk(KERN_ERR "led1 gpio request fail!\n");
		return ret;
	}
	gpio_direction_output(LED1_gpio, 1);
	
	x210_led_array_init(&x210_led);	
	ret = led_classdev_register(NULL,&x210_led);
	if (ret < 0) {
		printk(KERN_ERR "classdev register error in led \n");
		goto fail;
	}
	return 0;

fail:
	gpio_free(LED1_gpio);
	return ret;

}

static void __exit x210led_exit(void){
	led_classdev_unregister(&x210_led);
	gpio_free(LED1_gpio);
}



module_init(x210led_init);
module_exit(x210led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("lxs");
MODULE_DESCRIPTION("x210 led driver");
