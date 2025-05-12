[bits 32]  ; Ensure we are working in 32-bit mode

section .text
    global _irq0_handler
    global _isr0
    global _isr14
    global _isr_default
    global load_idt

; Default ISR that just returns
_isr_default:
    iret  ; Return from interrupt

; ISR for Divide Error (interrupt vector 0)
_isr0:
    pushad                  ; Save all registers
    ; You can add custom handling code for divide-by-zero interrupt here
    popad                   ; Restore registers
    iret                    ; Return from interrupt

; ISR for Page Fault (interrupt vector 14)
_isr14:
    pushad                  ; Save all registers
    ; You can add custom handling code for page fault interrupt here
    popad                   ; Restore registers
    iret                    ; Return from interrupt

; IRQ0 handler for the PIT interrupt
_irq0_handler:
    pushad
    call handle_interrupts  ; Ensure this matches the C code's function name
    popad
    iret

; External declaration for the C function to handle interrupts
extern handle_interrupts

; Linker data structure for the IDT descriptor
section .data
    global idt_descriptor
    idt_descriptor:
        dw 256*8 - 1          ; Limit
        dd _idt_table         ; Base address of the IDT table

section .bss
    align 16
    _idt_table:
        resb 256*8            ; Reserve space for 256 entries (each entry is 8 bytes)

; Function to load the IDT
section .text
load_idt:
    lidt [idt_descriptor]  ; Load the IDT descriptor into the IDTR register
    ret
