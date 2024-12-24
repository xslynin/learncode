CC = arm-linux-gcc
LD = arm-linux-ld
OBJCOPY = arm-linux-objcopy
OBJDUMP = arm-linux-objdump
AR = arm-linux-ar

OBJ := start.o main.o uart.o clock_init.o adc.o
OBJ += lib/libc.a

INCDIR := $(shell pwd)
# precompile
CPPFLAGS := -nostdlib -nostdinc -I$(INCDIR)/include
# compile 
CFLAGS 	 := -Wall -O2 -fno-builtin

export CC LD OBJCOPY OBJDUMP AR CPPFLAGS CFLAGS

target.bin:$(OBJ)
	$(LD) -Tlink.lds -o led.elf $^
	$(OBJCOPY) -O binary led.elf $@
	$(OBJDUMP) -D led.elf > led_eld.dis
	gcc mkv210_image.c -o mkx210
	./mkx210 target.bin 210.bin

lib/libc.a:
	cd lib && $(MAKE)

%.o : %.S
	arm-linux-gcc $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

%.o : %.c %.h
	arm-linux-gcc $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

.PHONY:clean
clean:
	rm *.o *.elf *.bin *.dis *mkx210* -f && cd lib && $(MAKE) clean
