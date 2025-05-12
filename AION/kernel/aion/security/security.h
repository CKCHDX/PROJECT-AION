// kernel/aion/security/security.h
#ifndef SECURITY_H
#define SECURITY_H

#include "permissions.h"
#include "../vga.h"

// Function prototypes from security_check.c
int validate_hardware_environment(void);
int verify_memory_boundaries(void* ptr);

// Function prototypes from validation.c
int validate_msr(unsigned msr);
int validate_io_port(unsigned port);

// Emergency functions
void emergency_shutdown(int reason);

#endif