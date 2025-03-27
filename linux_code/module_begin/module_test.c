#include <linux/module.h>
#include <linux/init.h>

static int __init chrdev_init(void){
	printk(KERN_ALERT "chrdev_init\n");
	return 0;
}

static void __exit chrdev_exit(void){
	printk(KERN_ALERT "chrdev_exit\n");
}

module_init(chrdev_init);
module_exit(chrdev_exit);

MODULE_LICENSE("GPL");
