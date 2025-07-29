[bits 32]  ; Ensure we are working in 32-bit mode

section .text
    global _irq0_handler
    global _isr0
    global _isr14
    global _isr_default
    global load_idt
    extern timer_tick_handler

; Default ISR that just returns
_isr_default:
    pushad                  ; Save all general purpose registers
    mov ax, ds              ; Save data segment
    push eax

    mov ax, 0x10            ; Load kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Could call a C handler here if needed

    pop eax                 ; Restore data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popad                   ; Restore all general purpose registers
    iret                    ; Return from interrupt

; ISR for Divide Error (interrupt vector 0)
_isr0:
    pushad
    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Handle divide by zero (could call a C handler)

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popad
    iret

; ISR for Page Fault (interrupt vector 14)
_isr14:
    pushad
    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Handle page fault (could call a C handler)

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popad
    add esp, 4             ; Clean up error code pushed by CPU for page faults
    iret

; IRQ0 handler for the PIT interrupt
_irq0_handler:
    pushad
    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call timer_tick_handler  ; Call the C handler

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popad
    iret

; Function to load the IDT
extern idt_ptr
section .text
load_idt:
    lidt [idt_ptr]
    ret
