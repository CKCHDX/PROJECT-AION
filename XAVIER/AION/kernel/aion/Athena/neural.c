// kernel/aion/brain/neural.c

#include "neural.h"
#include <math.h>
#include <stdint.h>
#include "prng.h"

// Emergency shutdown is provided elsewhere in the kernel:
extern void emergency_shutdown(int reason);

// Maximum PRNG value (must match prng.h implementation)
#define PRNG_MAX 0xFFFFFFFFu

// The one and only network instance
NeuralNetwork neural_network;

/** Sigmoid activation function */
static float sigmoid(float x) {
    return 1.0f / (1.0f + expf(-x));
}

void neural_init(void) {
    // 0) Guard rails: ensure layer sizes are valid
    if (INPUT_SIZE <= 0 || HIDDEN_SIZE <= 0 || OUTPUT_SIZE <= 0) {
        emergency_shutdown(0xDEADBEEF);
    }

    // 1) Seed PRNG from high-res timestamp counter (RDTSC)
    uint32_t lo, hi;
    uint64_t tsc;
    asm volatile("rdtsc" : "=a"(lo), "=d"(hi));
    tsc = ((uint64_t)hi << 32) | lo;
    prng_srand((uint32_t)(tsc ^ (tsc >> 32)));

    // 2) Initialize input→hidden weights & biases
    for (int i = 0; i < INPUT_SIZE; i++) {
        neural_network.input_layer[i].bias = ((float)prng_rand() / PRNG_MAX) * 2.0f - 1.0f;
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            neural_network.input_layer[i].weights[j] =
                ((float)prng_rand() / PRNG_MAX) * 2.0f - 1.0f;
        }
        neural_network.input_layer[i].last_output = 0.0f;
        neural_network.input_layer[i].activation_type = 0;
    }

    // 3) Initialize hidden→output weights & biases
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        neural_network.hidden_layer[i].bias = ((float)prng_rand() / PRNG_MAX) * 2.0f - 1.0f;
        for (int j = 0; j < OUTPUT_SIZE; j++) {
            neural_network.hidden_layer[i].weights[j] =
                ((float)prng_rand() / PRNG_MAX) * 2.0f - 1.0f;
        }
        neural_network.hidden_layer[i].last_output = 0.0f;
        neural_network.hidden_layer[i].activation_type = 0;
    }

    // 4) Initialize output biases
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        neural_network.output_layer[i].bias = ((float)prng_rand() / PRNG_MAX) * 2.0f - 1.0f;
        neural_network.output_layer[i].last_output = 0.0f;
        neural_network.output_layer[i].activation_type = 0;
    }

    // 5) Set default learning rate & reset training cycles
    neural_network.learning_rate = 0.01f;
    neural_network.training_cycles = 0;
}

float neural_forward(const float inputs[INPUT_SIZE]) {
    float hidden_outputs[HIDDEN_SIZE];

    // Input → Hidden
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        float sum = neural_network.hidden_layer[i].bias;
        for (int j = 0; j < INPUT_SIZE; j++) {
            sum += inputs[j] * neural_network.input_layer[j].weights[i];
        }
        hidden_outputs[i] = sigmoid(sum);
        neural_network.hidden_layer[i].last_output = hidden_outputs[i];
    }

    // Hidden → Output
    float total = 0.0f;
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        float sum = neural_network.output_layer[i].bias;
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            sum += hidden_outputs[j] * neural_network.hidden_layer[j].weights[i];
        }
        float out = sigmoid(sum);
        neural_network.output_layer[i].last_output = out;
        total += out;
    }

    // Return the mean output as a simple aggregated signal
    return total / OUTPUT_SIZE;
}

void neural_backprop(const float inputs[INPUT_SIZE],
                     const float targets[OUTPUT_SIZE]) {
    // Placeholder for backprop algorithm:
    // 1) Compute output errors (target - last_output)
    // 2) Compute hidden errors via weight-transposed backprop
    // 3) Update weights and biases using learning_rate
    // 4) Increment training_cycles

    // … your backprop implementation goes here …

    neural_network.training_cycles++;
}
