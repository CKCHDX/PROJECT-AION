#include "math.h"

float expf(float x) {
    // Taylor series approximation for exp(x)
    float sum = 1.0f;
    float term = 1.0f;
    for(int i = 1; i < 8; i++) {
        term *= x/i;
        sum += term;
    }
    return sum;
}