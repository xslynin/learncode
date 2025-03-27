#KERN_VER = $(shell uname -r)
KERN_VER = 2.6.35.7
KERN_DIR = /home/vx/Documents/kernel

PATH_dev = /usr/local/arm/arm-2009q3/bin/

obj-m += module_test.o
modname = module_test.ko

all:
	$(PATH_dev)arm-linux-gcc app.c -o app && cp app ~/nfsroot/rootfs/root/
	make -C $(KERN_DIR) M=`pwd` modules && cp $(modname) ~/nfsroot/rootfs/root/

.PHONY: clean
clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm app
