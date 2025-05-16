#include <stdint.h>

void int_to_string(int value, char* buffer) {
    char temp[12];
    int i = 0, j = 0;

    if (value == 0) {
        buffer[j++] = '0';
        buffer[j] = '\0';
        return;
    }

    while (value > 0) {
        temp[i++] = '0' + (value % 10);
        value /= 10;
    }

    while (i > 0) {
        buffer[j++] = temp[--i];
    }

    buffer[j] = '\0';
}
