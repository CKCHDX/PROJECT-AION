bits 64
section .note.GNU-stack noalloc noexec nowrite progbits

section .multiboot
align 8
mb_header:
    dd 0xE85250D6          ; Magic number
    dd 0                   ; Architecture (x86_64)
    dd mb_end - mb_header  ; Header length
    dd 0x100000000 - (0xE85250D6 + 0 + (mb_end - mb_header)) ; Checksum

    ; Optional tags (none needed for basic boot)
    dw 0    ; End tag type
    dw 0    ; Flags
    dd 8    ; Size
mb_end:

section .text
global _start
_start:
    mov rsp, stack_top
    and rsp, -16           ; Align stack to 16 bytes
    cld                    ; Clear direction flag
    extern kmain
    call kmain
    hlt

section .bss
align 16
stack_bottom:
    resb 4096
stack_top: