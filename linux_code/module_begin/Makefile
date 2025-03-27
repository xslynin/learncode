#KERN_VER = $(shell uname -r)
KERN_VER = 2.6.35.7
KERN_DIR = /home/vx/Documents/kernel

obj-m += module_test.o
modname = module_test.ko

all:
	make -C $(KERN_DIR) M=`pwd` modules && cp $(modname) ~/nfsroot/rootfs/root/

.PHONY: clean
clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
