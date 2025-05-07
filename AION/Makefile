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
AION_DIR       = $(KERNEL_SRC_DIR)/aion

all: $(ISO)

#-------------------------------------------------------------------------------
# Core boot + diagnostic + panel modules (unchanged)
#-------------------------------------------------------------------------------

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

memory_check.o: $(DIAG_DIR)/memory_check.c
	$(CC) $(CFLAGS) -c $< -o $@

drive_check.o: $(DIAG_DIR)/drive_check.c
	$(CC) $(CFLAGS) -c $< -o $@

gpu_check.o: $(DIAG_DIR)/gpu_check.c
	$(CC) $(CFLAGS) -c $< -o $@

fan_check.o: $(DIAG_DIR)/fan_check.c
	$(CC) $(CFLAGS) -c $< -o $@

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

#-------------------------------------------------------------------------------
# AION “core” replaced by stem/brain_stem and memory/ai_alloc
#-------------------------------------------------------------------------------

brain_stem.o: $(KERNEL_SRC_DIR)/aion/stem/brain_stem.c
	$(CC) $(CFLAGS) -c $< -o $@

memory_map.o: $(KERNEL_SRC_DIR)/aion/memory_map.c
	$(CC) $(CFLAGS) -c $< -o $@

scheduler.o: $(KERNEL_SRC_DIR)/aion/scheduler.c
	$(CC) $(CFLAGS) -c $< -o $@

ai_alloc.o: $(KERNEL_SRC_DIR)/aion/memory/ai_alloc.c
	$(CC) $(CFLAGS) -c $< -o $@

task.o: $(KERNEL_SRC_DIR)/aion/task.c
	$(CC) $(CFLAGS) -c $< -o $@

#-------------------------------------------------------------------------------
# Additional AION modules
#-------------------------------------------------------------------------------

# brain/
concept.o: $(KERNEL_SRC_DIR)/aion/brain/concept.c
	$(CC) $(CFLAGS) -c $< -o $@

intuition.o: $(KERNEL_SRC_DIR)/aion/brain/intuition.c
	$(CC) $(CFLAGS) -c $< -o $@

neural.o: $(KERNEL_SRC_DIR)/aion/brain/neural.c
	$(CC) $(CFLAGS) -c $< -o $@

# io/
direct_hw.o: $(KERNEL_SRC_DIR)/aion/io/direct_hw.c
	$(CC) $(CFLAGS) -c $< -o $@

effector.o: $(KERNEL_SRC_DIR)/aion/io/effector.asm
	$(ASM) $(ASMFLAGS) $< -o $@

sensor.o: $(KERNEL_SRC_DIR)/aion/io/sensor.asm
	$(ASM) $(ASMFLAGS) $< -o $@

aion.o: $(AION_DIR)/aion.c $(AION_DIR)/aion.h
	$(CC) $(CFLAGS) -c $< -o $@

sensory.o: $(AION_DIR)/io/sensory.c $(AION_DIR)/aion.h
	$(CC) $(CFLAGS) -c $< -o $@

action.o: $(AION_DIR)/io/action.c $(AION_DIR)/aion.h
	$(CC) $(CFLAGS) -c $< -o $@


# memory/
experience.o: $(KERNEL_SRC_DIR)/aion/memory/experience.c
	$(CC) $(CFLAGS) -c $< -o $@

state_save.o: $(KERNEL_SRC_DIR)/aion/memory/state_save.c
	$(CC) $(CFLAGS) -c $< -o $@

# security/
security_check.o: $(KERNEL_SRC_DIR)/aion/security/security_check.c
	$(CC) $(CFLAGS) -c $< -o $@

validation.o: $(KERNEL_SRC_DIR)/aion/security/validation.c
	$(CC) $(CFLAGS) -c $< -o $@

# stem/ (learning & reinforcement & survival already covered by brain_stem)
learning_loop.o: $(KERNEL_SRC_DIR)/aion/stem/learning_loop.c
	$(CC) $(CFLAGS) -c $< -o $@

reinforcement.o: $(KERNEL_SRC_DIR)/aion/stem/reinforcement.c
	$(CC) $(CFLAGS) -c $< -o $@

survival.o: $(KERNEL_SRC_DIR)/aion/stem/survival.c
	$(CC) $(CFLAGS) -c $< -o $@

# tests/
failsafe.o: $(KERNEL_SRC_DIR)/aion/tests/failsafe.c
	$(CC) $(CFLAGS) -c $< -o $@

firewall_test.o: $(KERNEL_SRC_DIR)/aion/tests/firewall_test.c
	$(CC) $(CFLAGS) -c $< -o $@

#-------------------------------------------------------------------------------
# Final linking
#-------------------------------------------------------------------------------

$(KERNEL): boot.o kernel.o vga.o delays.o utils.o \
           memory_check.o drive_check.o gpu_check.o fan_check.o \
           control_panel.o input.o hardware_check.o aion_check.o reset.o boot_AION.o \
           aion.o brain_stem.o memory_map.o scheduler.o ai_alloc.o task.o \
           concept.o intuition.o neural.o direct_hw.o effector.o sensor.o sensory.o action.o \
           experience.o state_save.o security_check.o validation.o \
           learning_loop.o reinforcement.o survival.o failsafe.o firewall_test.o
	$(LD) $(LDFLAGS) -o $@ $^

#-------------------------------------------------------------------------------
# ISO creation & helpers
#-------------------------------------------------------------------------------

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
