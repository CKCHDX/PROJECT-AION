// In security/validation.c
#include "security.h"

const unsigned allowed_msrs[] = ALLOWED_MSRS;
const unsigned allowed_ports[] = ALLOWED_SENSOR_PORTS;

int validate_msr(unsigned msr) {
    for(int i=0; i<sizeof(allowed_msrs)/sizeof(unsigned); i++) {
        if(msr == allowed_msrs[i]) return 0;
    }
    return -1;
}

int validate_io_port(unsigned port) {
    for(int i=0; i<sizeof(allowed_ports)/sizeof(unsigned); i++) {
        if(port == allowed_ports[i]) return 0;
    }
    return -1;
}