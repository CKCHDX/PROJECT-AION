#include "../aion/stem/brain_stem.h"
#include "../vga.h"
#include "../aion/aion.h"  // Corrected path

void boot_aion() {
    vga_clear();
    aion_start();
}
