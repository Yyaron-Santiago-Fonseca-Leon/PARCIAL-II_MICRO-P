CROSS = riscv64-unknown-elf-
CC = $(CROSS)gcc
OBJCOPY = $(CROSS)objcopy

CFLAGS = -march=rv32ima_zicsr -mabi=ilp32 -Wall -g -O0 -ffreestanding -nostdlib -Iinc

all: program.bin

program.elf: Start.S main.c src/soc_emu_gpio.c link.ld
	$(CC) $(CFLAGS) -T link.ld Start.S main.c src/soc_emu_gpio.c -o program.elf
	$(OBJCOPY) -O binary program.elf program.bin

program.bin: program.elf
	$(OBJCOPY) -O binary program.elf program.bin

clean:
	rm -f *.o *.elf *.bin
