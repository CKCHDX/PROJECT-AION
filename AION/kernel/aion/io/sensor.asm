[bits 32]
global read_sensor

read_sensor:
    ; Input: EDI = sensor ID
    ; Output: EAX = sensor value
    mov dx, di
    in eax, dx
    ret
