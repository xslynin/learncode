/*
 *	in this file , try the static address map and the dynamic map application
 *	the static way by write, while the dynamic one only run in the init function in short
 * 
 * */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank.h>
#include <linux/string.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/cdev.h>
#include <linux/device.h>


#define THISNAME 	"test_drv"

#if 1
#define MINORCOUNT 	1
#define MYMAJOR 	200
#endif

//there get the virtual address for physical address

#define	rGPJ0CON *((unsigned int *)S5PV210_GPJ0CON)
#define rGPJ0DAT *((unsigned int *)S5PV210_GPJ0DAT)

#define GPJ0CON_PHY 0xE0200240

static int Module_Major;
static char buf[100];
static unsigned int * gpj0con;
static unsigned int * gpj0dat;
static struct class * test_class;

#if 1
static dev_t mydev;
static struct cdev test_cdev;
#endif

static int my_chrdev_open(struct inode *inode, struct file *file){
	// what really need is the operation code for hardware
	printk(KERN_INFO "configuration the gpio port for output \n");
	//in open(), we need to do some init of hardware but do not implement fair
//	rGPJ0CON = 0x11111111;

	return 0;
}

static int single_release(struct inode * inode, struct file *file){
	printk(KERN_INFO "test release \n");

	return 0;
}

static ssize_t led_read(struct file *file, char __user *buffer, size_t size, loff_t *pos){
	//copy_to_user();
	//implement something, but ignore there in led
	return 0;
}

static ssize_t led_write (struct file *file, const char __user *buffer, size_t size, loff_t *pos){
	//receive the fair and implement the hardware funciton
/*
	unsigned int ret;	
	ret = copy_from_user(buf, buffer, size);	
	if(ret != 0){
		printk(KERN_ERR "it seems that the copy from user failed\n");
	}
	
	if(!strcmp(buf,"on")){
		//turn on the led
		rGPJ0DAT = (0 << 3)|(0 << 4)|(0 << 5);
	}
	else if (!strcmp(buf,"off")){
		//turn off the led
		rGPJ0DAT = (1 << 3)|(1<<4)|(1<<5);
	}
*/
	return 0;
}

//construct a struct variable file_operation
 static const struct file_operations test_fops = {
	.owner		= THIS_MODULE,
	.open		= my_chrdev_open,	//use when open in aplication
	.read		= led_read,			//from drive to application
	.write		= led_write,		//from application to drive  cause the .write -> write() is used by the app!
	.release	= single_release,				//.open response to,  equal to the function call of close();;
};


static int __init chrdev_init(void){
	int retval;
	printk(KERN_ALERT "chrdev_init\n");
	//registe our driver
	//arg 0 means automatically choose major by kernel
	//and the return is what the major actually is , for the unregiste
/*
	Module_Major = register_chrdev(0, THISNAME, &test_fops);
	if(Module_Major < 0){
		printk(KERN_ERR "chrdev_register fail!\n");
		return -EINVAL;
	}
	printk(KERN_INFO "register chrdev success! %d is this device \n", Module_Major);
*/
	// new way to register the driver
	// first , registe and allocate the major number and minor number
	// when allocate automatically, only this step should change
/*	
	mydev = MKDEV(MYMAJOR, 0);
	retval = register_chrdev_region(mydev, MINORCOUNT, THISNAME);
	if(retval){
		printk(KERN_ERR "Unable to register minors for %d \n", MYMAJOR);
		return -1;
	}

*/	
	retval = alloc_chrdev_region(&mydev,0,MINORCOUNT,"test_dev");
	if(retval){
		printk(KERN_ERR "Unable to allocate\n");
		return -1;
	}
	printk(KERN_INFO "allocate done, major= %d ,minor= %d\n", MAJOR(mydev), MINOR(mydev));
	

	// second , registe the drive
	cdev_init(&test_cdev, &test_fops);
	retval = cdev_add(&test_cdev, mydev, MINORCOUNT);
	if(retval){
		printk(KERN_ERR "Unable to cdev_add\n");
		return -1;
	}
	printk(KERN_INFO "cdev_registe \n");
	
	// connect udev, the application level's app, used for the interface between user level and kernel level,
	// automatically create the driver file in /dev with named there
	test_class = class_create(THIS_MODULE, "test_class");
	if(IS_ERR(test_class)){
		return -1;
	}
	device_create(test_class, NULL, mydev, NULL, "test");


	//test function
	if(!request_mem_region(GPJ0CON_PHY, 8,"GPJ0CON"))
		return -1;
	gpj0con = ioremap(GPJ0CON_PHY, 8);
	gpj0dat = gpj0con + 1;
	
	*gpj0con = 0x11111111;
	*gpj0dat = (0 << 3)|(0 << 4)|(0 << 5);
	return 0;
}

static void __exit chrdev_exit(void){
	printk(KERN_ALERT "chrdev_exit\n");
	
	*gpj0dat = (1 << 3)|(1<<4)|(1<<5);
	iounmap(gpj0con);
	release_mem_region(GPJ0CON_PHY, 8);

	device_destroy(test_class, mydev);
	class_destroy(test_class);	
	//delete the cdev first and then unregister the device number
	cdev_del(&test_cdev);
	unregister_chrdev_region(mydev, MINORCOUNT);


	//unregiste
//	unregister_chrdev(Module_Major, THISNAME);
}

module_init(chrdev_init);
module_exit(chrdev_exit);

MODULE_LICENSE("GPL");
