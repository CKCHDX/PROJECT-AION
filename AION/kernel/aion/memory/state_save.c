// kernel/aion/memory/state_save.c
#include "state_save.h"
#include "../brain/neural.h"
#include "../io/ata.h" 
#include <stddef.h>

#define LBA_START 0x1000

static uint32_t checksum_memory(const void* data, size_t size) {
    const uint8_t* bytes = (const uint8_t*)data;
    uint32_t sum = 0;
    for(size_t i = 0; i < size; i++) {
        sum = (sum << 5) - sum + bytes[i];
    }
    return sum;
}

void neural_save_state(void) {
    ata_write(LBA_START, &neural_network, sizeof(NeuralNetwork));
    uint32_t chk = checksum_memory(&neural_network, sizeof(NeuralNetwork));
    ata_write(LBA_START + 1, &chk, sizeof(chk));
}