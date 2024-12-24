###这里bl2不需要bin头，因此去掉了那个部分
target2.bin: start.o main.o lcd.o
	arm-linux-ld -Tlink.lds -o target2.elf $^
	arm-linux-objcopy -O binary target2.elf $@
	arm-linux-objdump -D target2.elf > target2_elf.dis

%.o : %.S
	arm-linux-gcc -o $@ $< -c -nostdlib

%.o : %.c
	arm-linux-gcc -o $@ $< -c -nostdlib

clean:
	rm *.o *.elf *.bin *.dis -f

	
	
