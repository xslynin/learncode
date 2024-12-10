OBJ := start.o main.o uart.o clock_init.o
target.bin:$(OBJ)
	arm-linux-ld -Tlink.lds -o led.elf $^
	arm-linux-objcopy -O binary led.elf $@
	arm-linux-objdump -D led.elf > led_eld.dis

%.o : %.S
	arm-linux-gcc -o $@ $< -c -nostdlib

%.o : %.c %.h
	arm-linux-gcc -o $@ $< -c -nostdlib

.PHONY:clean
clean:
	rm *.o *.elf *.bin *.dis -f
