ENTRY(_start)
OUTPUT_FORMAT(elf64-x86-64)

SECTIONS {
    . = 1M; /* Load address starts at 1MB */

    .multiboot : {
        *(.multiboot)
    }

    .text : ALIGN(4K) {
        *(.text*)
    }

    .rodata : ALIGN(4K) {
        *(.rodata*)
    }

    .data : ALIGN(4K) {
        *(.data*)
    }

    .bss : ALIGN(4K) {
        *(COMMON)
        *(.bss*)
        . = ALIGN(16);

        stack_bottom = .;
        . += 4096; /* 4KB stack */
        stack_top = .;
    }
}
