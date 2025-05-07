#ifndef PERMISSIONS_H
#define PERMISSIONS_H
#define VGA_BUFFER_START 0xB8000
#define VGA_BUFFER_END   0xB8FA0

#define AI_ALLOWED_MEMORY_START VGA_BUFFER_START
#define AI_ALLOWED_MEMORY_END   VGA_BUFFER_END
#define AI_PROHIBITED_ADDRESSES {0x00000000, 0xFFFFFFFF}

typedef enum {
    HW_ACCESS_NONE = 0,
    HW_ACCESS_READ_ONLY,
    HW_ACCESS_FULL
} hw_permission_level;

struct DevicePermissions {
    unsigned int device_id;
    hw_permission_level level;
};
// Add these at the bottom
int validate_hardware_environment(void);
int verify_memory_boundaries(void* ptr);
#endif
