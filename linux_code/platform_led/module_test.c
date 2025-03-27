/*
 *	In this file, register led gpio by another way , that is , register it in sys/class	
 *	
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/leds.h>
#include <linux/gpio.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/platform_device.h>
#include <linux/slab.h>

#include <mach/regs-gpio.h>
#include <mach/gpio-bank.h>
#include <mach/gpio.h>
#include <mach/leds-gpio.h>


struct x210_gpio_led {
	struct led_classdev cdev;
	struct s3c24xx_led_platdata	*pdata;
};

static void x210_led_set(struct led_classdev *led_cdev, enum led_brightness value){
	struct x210_gpio_led * led = container_of(led_cdev, struct x210_gpio_led, cdev);
	struct s3c24xx_led_platdata * pdata = led->pdata;
	
	//apply for gpio
	if(gpio_request(pdata->gpio, "x210led_set")){
		printk(KERN_ERR "led gpio request failed in set function\n");
		return;
	}


	//turn on the led
	if(value != 0){
		printk(KERN_INFO "turn on the led\n");
		gpio_set_value(pdata->gpio, 0);
//		writel(((0<<3)|(0<<4)|(0<<5)), S5PV210_GPJ0DAT);
	}else{//close the led
		printk(KERN_INFO "turn off the led\n");
		gpio_set_value(pdata->gpio, 1);
//		writel(((1<<3)|(1<<4)|(1<<5)), S5PV210_GPJ0DAT);
	}
	gpio_free(pdata->gpio);
}


//register the led class like the previous init
static int x210_led_probe(struct platform_device * plt_dev){
	struct s3c24xx_led_platdata *pdata = plt_dev->dev.platform_data;
	struct x210_gpio_led *led;
	int ret;

	led = kzalloc(sizeof(struct x210_gpio_led), GFP_KERNEL);
	if(led == NULL){
		dev_err(&plt_dev->dev, "No memory for device \n");
		return -ENOMEM;
	}
	
	platform_set_drvdata(plt_dev, led);
	led->cdev.brightness_set = x210_led_set;
	led->cdev.name = pdata->name;
	led->cdev.brightness = 0;
	led->cdev.max_brightness = 255;
	led->pdata = pdata;

	if(gpio_request(pdata->gpio, "test")){
		printk(KERN_ERR "led%d gpio request fail!\n", plt_dev->id);
		return -1;
	}
	gpio_direction_output(pdata->gpio, 1);
	gpio_free(pdata->gpio);


	ret = led_classdev_register(&plt_dev->dev,&led->cdev);
	if(ret < 0){
		dev_err(&plt_dev-> dev, "led classdev register failed! ret= %d \n", ret);
		kfree(led);
		return ret;
	}

	return 0;
}

static int x210_led_remove(struct platform_device * plt_dev){
	struct x210_gpio_led *led = (struct x210_gpio_led *)platform_get_drvdata(plt_dev);
	
	led_classdev_unregister(&led->cdev);
	if(led == NULL){
		goto end;	
	}
	kfree(led);
end:
	return 0;
}



//this level you can only see the driver function
//the data is faded behind the device level in platform
//in the platform struction, the probe function is packaged in abstract level
//funciton in this file is the true function to behave
struct platform_driver x210_led_driver = {
	.probe		= x210_led_probe,
	.remove		= x210_led_remove,
	.driver		= {
		.name	= "x210_led",
		.owner  = THIS_MODULE,
	},

};


static int __init x210led_init(void){
	return platform_driver_register(&x210_led_driver);
}

static void __exit x210led_exit(void){
	platform_driver_unregister(&x210_led_driver);
}



module_init(x210led_init);
module_exit(x210led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("lxs");
MODULE_DESCRIPTION("x210 led driver");
MODULE_ALIAS("platform:x210_led");
