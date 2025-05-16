#include <stdint.h>

void simple_delay(int count) {
    volatile int i;
    // Increase the iterations for longer delay
    for (i = 0; i < count * 10; i++) {  // Multiply count for more delay
        // Busy-wait loop, do nothing
    }
}
