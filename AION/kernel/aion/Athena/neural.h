// kernel/aion/brain/neural.h

#ifndef NEURAL_H
#define NEURAL_H

#include <stdint.h>

#define INPUT_SIZE   32
#define HIDDEN_SIZE  64
#define OUTPUT_SIZE  16
#define NETWORK_SIZE (INPUT_SIZE + HIDDEN_SIZE + OUTPUT_SIZE)

/**
 * A single neuron: holds its incoming weights (size = size of previous layer),
 * a bias term, and last_output for backprop bookkeeping.
 */
typedef struct Neuron {
    float weights[INPUT_SIZE];   // max needed is INPUT_SIZE; hidden→output reuses same struct
    float bias;
    float last_output;
    uint8_t activation_type;     // reserve for future (e.g. sigmoid vs relu)
} Neuron;

/**
 * The full neural network: three layers of Neuron, plus learning rate
 * and a count of how many times we've trained.
 */
typedef struct NeuralNetwork {
    Neuron input_layer[INPUT_SIZE];
    Neuron hidden_layer[HIDDEN_SIZE];
    Neuron output_layer[OUTPUT_SIZE];
    float learning_rate;
    unsigned long training_cycles;
} NeuralNetwork;

// The global network instance
extern NeuralNetwork neural_network;

// Initialize network weights/biases, seed PRNG, guard rails
void neural_init(void);

// Run a forward pass: returns the average of output neurons
float neural_forward(const float inputs[INPUT_SIZE]);

// Perform one backprop step toward the given targets
void neural_backprop(const float inputs[INPUT_SIZE], const float targets[OUTPUT_SIZE]);

// Save network state to non-volatile storage (stub/prototype)
void neural_save_state(void);

#endif // NEURAL_H
