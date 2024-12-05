led.bin:led.o
	arm-linux-ld -Ttext 0x0 -o led.elf $^
	arm-linux-objcopy -O binary led.elf led.bin
	arm-linux-objdump -D led.elf > led_eld.dis

%.o : %.S
	arm-linux-gcc -o $@ $< -c

%.o : %.c
	arm-linux-gcc -o $@ $< -c

.PHONY:clean
clean:
	rm *.o *.elf *.bin *.dis -f
