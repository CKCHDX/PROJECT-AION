[bits 32]
section .note.GNU-stack noalloc noexec nowrite progbits

global read_msr
global read_port
global read_temp

; Read Model Specific Register (CPU Temp)
; Input: ECX = MSR address
; Output: EDX:EAX = result
read_msr:
    rdmsr
    ret

; Read I/O port (Generic sensor)
; Input: EDI = port
; Output: EAX = value
read_port:
    xor eax, eax
    mov dx, di
    in eax, dx
    ret

; Real temperature sensor read (Intel/AMD specific)
; Returns temperature in Celsius
read_temp:
    mov ecx, 0x1A2  ; IA32_THERM_STATUS
    rdmsr
    shr eax, 16
    and eax, 0x7F   ; Temp in Celsius
    ret
