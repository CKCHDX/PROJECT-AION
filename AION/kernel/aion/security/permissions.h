#ifndef PERMISSIONS_H
#define PERMISSIONS_H

// Memory boundaries
#define VGA_BUFFER_START 0xB8000
#define VGA_BUFFER_END   0xB8FA0

// Hardware permissions
#define AI_ALLOWED_MEMORY_START VGA_BUFFER_START
#define AI_ALLOWED_MEMORY_END   VGA_BUFFER_END

// Valid MSR addresses (actual Intel MSRs)
#define ALLOWED_MSRS {0x1A2, 0x3A, 0x1B}  // IA32_THERM_STATUS, IA32_FEATURE_CONTROL, APIC_BASE

// Valid I/O ports
#define ALLOWED_SENSOR_PORTS {0xE2, 0xE4, 0x2E, 0x70, 0x71}

typedef enum {
    HW_ACCESS_NONE = 0,
    HW_ACCESS_READ_ONLY,
    HW_ACCESS_FULL
} hw_permission_level;

struct DevicePermissions {
    unsigned int device_id;
    hw_permission_level level;
};

#endif