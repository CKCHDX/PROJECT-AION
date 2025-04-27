#include <stdint.h>

volatile uint16_t* vga = (uint16_t*)0xB8000;  // VGA memory address

// Screen dimensions (80x25 for text mode)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Function to clear the screen
void clear_screen() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga[i] = (0x0F << 8) | ' ';  // Black background, white text
    }
}

// Function to write a message at the top-left corner of the screen
void print_message(const char* msg) {
    int i = 0;
    while (msg[i] != '\0') {
        vga[i] = (0x0F << 8) | msg[i];  // White text on black background
        i++;
    }
}

void kmain() {
    // Clear the screen
    clear_screen();
    
    // Write message
    const char* msg = "AION BRAIN STEM 64";
    print_message(msg);

    // Halt the system (infinite loop)
    while(1) {
        __asm__ volatile ("hlt");
    }
}
