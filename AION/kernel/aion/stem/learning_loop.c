#include "../aion.h"

float prediction_error = 0.0f;

// Implementations must match declarations in aion.h
float get_prediction(void) {
    return 0.0f; // TODO: Implement
}

float get_outcome(void) {
    return 0.0f; // TODO: Implement
}

void adjust_weights(float error) {
    // TODO: Implement
}

void run_learning_cycle(void) {
    float current_prediction = get_prediction();
    float actual_outcome = get_outcome();

    prediction_error = actual_outcome - current_prediction;
    adjust_weights(prediction_error);
}
