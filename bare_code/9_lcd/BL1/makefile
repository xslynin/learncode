target1.bin: start.o sdram_init.o sd_relocate.o
	arm-linux-ld -Tlink.lds -o target1.elf $^
	arm-linux-objcopy -O binary target1.elf $@
	arm-linux-objdump -D target1.elf > target1_elf.dis
	gcc mkv210_image.c -o mkx210
	./mkx210 $@ BL1.bin
	
%.o : %.S
	arm-linux-gcc -o $@ $< -c -nostdlib

%.o : %.c
	arm-linux-gcc -o $@ $< -c -nostdlib

clean:
	rm *.o *.elf *.bin *.dis mkx210 -f

	
	