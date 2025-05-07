; boot/boot.S — Minimal Multiboot2 header for an ELF kernel
BITS 32

SECTION .multiboot ALIGN=8
    dd 0xE85250D6            ; magic
    dd 0                     ; arch = i386
    dd header_end - header   ; total header length
    dd -(0xE85250D6 + 0 + (header_end - header))

header:
    dd 0                     ; tag type = END
    dd 8                     ; tag size = 8
header_end:

SECTION .text
global _start
extern kernel_main

_start:
    cli
    mov esp, stack_top
    call kernel_main
    hlt

SECTION .bss
ALIGN 16
stack_bottom:
    resb 8192
stack_top:
