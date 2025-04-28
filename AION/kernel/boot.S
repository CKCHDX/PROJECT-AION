/* Multiboot2 Header */
.section .multiboot
.align 8
mb_header:
    .long 0xE85250D6       /* Magic number */
    .long 0                /* Architecture (x86_64) */
    .long mb_header_end - mb_header /* Header length */
    .long -(0xE85250D6 + 0 + (mb_header_end - mb_header)) /* Checksum */

    /* Video mode tag (Framebuffer) */
    .short 5               /* Type = Framebuffer */
    .short 1               /* Flags = optional */
    .long 20               /* Size = 20 bytes */
    .long 80               /* Width (columns) */
    .long 25               /* Height (rows) */
    .long 0                /* Depth (0 = text mode) */

    /* Memory map tag (optional) */
    .short 6               /* Type = Memory map */
    .short 1               /* Flags = optional */
    .long 12               /* Size = 12 bytes */
    .long 0                /* Base address of the memory map */
    .long 0                /* Length of the memory map */
    .long 0                /* Type of memory */

    /* ELF sections tag (optional) */
    .short 9               /* Type = ELF sections */
    .short 1               /* Flags = optional */
    .long 12               /* Size = 12 bytes */
    .long 0                /* Address of ELF section headers */
    .long 0                /* Size of ELF section headers */
    .long 0                /* Number of ELF sections */

    /* End tag */
    .short 0               /* Type */
    .short 0               /* Flags */
    .long 8                /* Size */
mb_header_end:

/* Kernel Entry Point */
.section .text
.global _start
_start:
    cli
    mov $stack_top, %rsp
    and $-16, %rsp       /* 16-byte align stack */
    call kmain
    cli
1:  hlt
    jmp 1b

.section .bss
.align 16
stack_bottom:
    .skip 4096
stack_top:
