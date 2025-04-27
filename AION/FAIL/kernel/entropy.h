#ifndef ENTROPY_H
#define ENTROPY_H

#include <stdint.h>
#include <stddef.h>

void analyze_port(uint16_t port);
double compute_entropy(uint8_t* data, size_t len);
void log_entropy(uint16_t port, double entropy);

#endif