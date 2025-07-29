#include "memory_check.h"
#include "vga.h"
#include <stddef.h>  // Include for size_t

#define TEST_MEMORY_START 0x1000      // Start address for testing
#define TEST_MEMORY_END   0x8000      // End address for testing (increase range)
#define PATTERN_A          0xAA       // Pattern A (alternating 1s)
#define PATTERN_B          0x55       // Pattern B (alternating 0s)

// Forward declaration of test_memory_region function
static int test_memory_region(volatile uint32_t* addr, uint32_t pattern, size_t size);

// Function to test a specific memory region with the given pattern
static int test_memory_region(volatile uint32_t* addr, uint32_t pattern, size_t size) {
    // Write the pattern to the memory region
    for (size_t i = 0; i < size / sizeof(uint32_t); i++) {
        addr[i] = pattern;
        simple_delay(1000);  // Add a small delay between each write operation
    }
    
    // Read back and verify the data
    for (size_t i = 0; i < size / sizeof(uint32_t); i++) {
        if (addr[i] != pattern) {
            return 0; // Memory mismatch detected
        }
        simple_delay(1000);  // Add a small delay between each read operation
    }

    return 1; // Memory region is fine
}


int check_memory() {
    // Start testing memory at TEST_MEMORY_START to TEST_MEMORY_END
    volatile uint32_t* addr = (volatile uint32_t*)TEST_MEMORY_START;

    // Test the first memory region with pattern A
    if (!test_memory_region(addr, PATTERN_A, TEST_MEMORY_END - TEST_MEMORY_START)) {
        return 0; // Memory check failed at region 1
    }

    // Test another memory region with pattern B
    addr = (volatile uint32_t*)TEST_MEMORY_START + 0x100;  // Just shift a little
    if (!test_memory_region(addr, PATTERN_B, TEST_MEMORY_END - TEST_MEMORY_START)) {
        return 0; // Memory check failed at region 2
    }

    // Optionally, test more regions of memory...

    return 1; // If all tests pass, memory is considered OK
}
