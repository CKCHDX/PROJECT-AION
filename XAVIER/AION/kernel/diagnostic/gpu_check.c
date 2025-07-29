#include "gpu_check.h"
#include <stdint.h>

int check_gpu() {
    uint16_t success;
    __asm__ volatile (
        "mov $0x4F00, %%ax\n"
        "int $0x10\n"
        "mov %%ax, %0\n"
        : "=r"(success)
        :
        : "ax"
    );

    return (success == 0x004F);
}
