#include <stdint.h>
#include "input.h"

#define KEYBOARD_DATA_PORT 0x60

char wait_for_keypress() {
    uint8_t scancode = 0;
    char key = 0;

    while (1) {
        // Read from port 0x60 if key has been pressed
        asm volatile("inb %1, %0" : "=a"(scancode) : "Nd"(KEYBOARD_DATA_PORT));

        // Basic scancode to ASCII (only ENTER and 'R'/'r' here)
        if (scancode == 0x1C) return '\n';       // ENTER key
        if (scancode == 0x13) return 'r';        // 'R' key
        if (scancode == 0x2D) return 'r';        // 'R' key lowercase (same scancode)
    }

    return key;
}
