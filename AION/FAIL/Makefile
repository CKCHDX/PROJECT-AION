C_SOURCES = $(wildcard kernel/*.c)
OBJS = $(patsubst kernel/%.c, build/kernel/%.o, $(C_SOURCES))

CFLAGS = -ffreestanding -mcmodel=large -mno-red-zone -nostdlib -fno-builtin

all: build/aion.iso

build/aion.iso: build/kernel.elf
	mkdir -p build/iso/boot/grub
	cp build/kernel.elf build/iso/boot/
	echo 'menuentry "AION" { multiboot2 /boot/kernel.elf }' > build/iso/boot/grub/grub.cfg
	grub-mkrescue -o build/aion.iso build/iso

build/kernel.elf: build/boot.o $(OBJS)
	ld -T boot/linker.ld -o $@ $^ -nostdlib

build/boot.o: boot/boot.asm
	mkdir -p $(dir $@)
	nasm -f elf64 $< -o $@

build/kernel/%.o: kernel/%.c
	mkdir -p $(dir $@)
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -rf build

.PHONY: all clean