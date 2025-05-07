[bits 32]
global write_effector

write_effector:
    ; Input: EDI = device ID, ESI = value
    mov dx, di
    mov eax, esi
    out dx, eax
    ret
