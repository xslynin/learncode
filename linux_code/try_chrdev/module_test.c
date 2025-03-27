#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

#define THISNAME "testchrdev"

static int Module_Major;

static int my_chrdev_open(struct inode *inode, struct file *file){
	// what really need is the operation code for hardware
	printk(KERN_INFO "test my chrdev open \n");

	return 0;
}

static int single_release(struct inode * inode, struct file *file){
	printk(KERN_INFO "test release \n");

	return 0;
}

//construct a struct variable file_operation
 static const struct file_operations test_fops = {
	.owner		= THIS_MODULE,
	.open		= my_chrdev_open,	//use when open in aplication
//	.read		= seq_read,
//	.llseek		= seq_lseek,
	.release	= single_release,				//.open response to ???
};


static int __init chrdev_init(void){
	printk(KERN_ALERT "chrdev_init\n");
	//registe our driver
	//arg 0 means automatically choose major by kernel
	//and the return is what the major actually is , for the unregiste
	Module_Major = register_chrdev(0, THISNAME, &test_fops);
	if(Module_Major < 0){
		printk(KERN_ERR "chrdev_register fail!\n");
		return -EINVAL;
	}
	printk(KERN_INFO "register chrdev success! %d is this device \n", Module_Major);
	return 0;
}

static void __exit chrdev_exit(void){
	printk(KERN_ALERT "chrdev_exit\n");
	//unregiste
	unregister_chrdev(Module_Major, THISNAME);
}

module_init(chrdev_init);
module_exit(chrdev_exit);

MODULE_LICENSE("GPL");
