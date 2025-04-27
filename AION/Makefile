CC = gcc
LD = ld
CFLAGS = -m64 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector
LDFLAGS = -T boot/linker.ld
OBJ = boot.o main.o

all: aion.iso

aion.iso: kernel.elf
	mkdir -p iso/boot/grub
	cp kernel.elf iso/boot/
	cp boot/grub.cfg iso/boot/grub/
	grub-mkrescue -o aion.iso iso

kernel.elf: $(OBJ)
	$(LD) $(LDFLAGS) -o kernel.elf $(OBJ)

boot.o: kernel/boot.S
	$(CC) $(CFLAGS) -c kernel/boot.S -o boot.o

main.o: kernel/main.c
	$(CC) $(CFLAGS) -c kernel/main.c -o main.o

clean:
	rm -rf iso *.o *.elf *.iso
