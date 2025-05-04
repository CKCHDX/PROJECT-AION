CC      = gcc
LD      = ld
ASM     = nasm

# 32-bit Compilation Flags
CFLAGS = -ffreestanding -nostdlib -m32 -O1 -fno-pic -no-pie -fno-stack-protector \
         -Ikernel -Ikernel/diagnostic -Ikernel/panel -Ikernel/aion

LDFLAGS  = -nostdlib -static -T boot/linker.ld -m elf_i386
ASMFLAGS = -f elf32

KERNEL   = kernel.bin
ISO      = aion.iso

# Source directories
KERNEL_SRC_DIR = kernel
BOOT_SRC_DIR   = boot
DIAG_DIR       = $(KERNEL_SRC_DIR)/diagnostic

all: $(ISO)

# Kernel and diagnostic modules
kernel.o: $(KERNEL_SRC_DIR)/kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

vga.o: $(KERNEL_SRC_DIR)/vga.c
	$(CC) $(CFLAGS) -c $< -o $@


delays.o: $(KERNEL_SRC_DIR)/utils.c
	$(CC) $(CFLAGS) -c $< -o $@

utils.o: $(KERNEL_SRC_DIR)/delays.c
	$(CC) $(CFLAGS) -c $< -o $@

boot.o: $(BOOT_SRC_DIR)/boot.S
	$(ASM) $(ASMFLAGS) $< -o $@

# Diagnostic modules


memory_check.o: $(DIAG_DIR)/memory_check.c
	$(CC) $(CFLAGS) -c $< -o $@

drive_check.o: $(DIAG_DIR)/drive_check.c
	$(CC) $(CFLAGS) -c $< -o $@

gpu_check.o: $(DIAG_DIR)/gpu_check.c
	$(CC) $(CFLAGS) -c $< -o $@

fan_check.o: $(DIAG_DIR)/fan_check.c
	$(CC) $(CFLAGS) -c $< -o $@

# Panel modules
control_panel.o: $(KERNEL_SRC_DIR)/panel/control_panel.c
	$(CC) $(CFLAGS) -c $< -o $@

input.o: $(KERNEL_SRC_DIR)/panel/input.c
	$(CC) $(CFLAGS) -c $< -o $@

hardware_check.o: $(KERNEL_SRC_DIR)/panel/hardware_check.c
	$(CC) $(CFLAGS) -c $< -o $@

aion_check.o: $(KERNEL_SRC_DIR)/panel/aion_check.c
	$(CC) $(CFLAGS) -c $< -o $@

reset.o: $(KERNEL_SRC_DIR)/panel/reset.c
	$(CC) $(CFLAGS) -c $< -o $@

boot_AION.o: $(KERNEL_SRC_DIR)/panel/boot.c
	$(CC) $(CFLAGS) -c $< -o $@

# AION core module
aion_core.o: $(KERNEL_SRC_DIR)/aion/aion_core.c
	$(CC) $(CFLAGS) -c $< -o $@

memory_map.o: $(KERNEL_SRC_DIR)/aion/memory_map.c
	$(CC) $(CFLAGS) -c $< -o $@

scheduler.o: $(KERNEL_SRC_DIR)/aion/scheduler.c
	$(CC) $(CFLAGS) -c $< -o $@

memory_manager.o: $(KERNEL_SRC_DIR)/aion/memory_manager.c
	$(CC) $(CFLAGS) -c $< -o $@

task.o: $(KERNEL_SRC_DIR)/aion/task.c
	$(CC) $(CFLAGS) -c $< -o $@



# Final linking
$(KERNEL): boot.o kernel.o vga.o delays.o utils.o \
           memory_check.o drive_check.o gpu_check.o fan_check.o \
           control_panel.o input.o hardware_check.o aion_check.o reset.o boot_AION.o \
           aion_core.o memory_map.o scheduler.o memory_manager.o task.o

	$(LD) $(LDFLAGS) -o $@ $^


# ISO creation
$(ISO): $(KERNEL)
	mkdir -p isodir/boot/grub
	cp $(KERNEL) isodir/boot/
	cp grub/grub.cfg isodir/boot/grub/
	grub-mkrescue -o $(ISO) isodir

clean:
	rm -f *.o $(KERNEL) $(ISO)
	rm -rf isodir

run: $(ISO)
	qemu-system-x86_64 -cdrom $(ISO) -vga std -display curses
