led.bin:start.o led.o
	arm-linux-ld -Tlink.lds -o led.elf $^
	arm-linux-objcopy -O binary led.elf led.bin
	arm-linux-objdump -D led.elf > led_eld.dis

%.o : %.S
	arm-linux-gcc -o $@ $< -c -nostdlib

%.o : %.c
	arm-linux-gcc -o $@ $< -c -nostdlib

.PHONY:clean
clean:
	rm *.o *.elf *.bin *.dis -f
