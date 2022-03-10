#include "libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    int length = 0;
    unsigned long num = 0;
    unsigned long base = 1;
    if (hex != NULL) {
        while (hex[length]) {
            length++;
        }
    }
    else {
        return 0;
    }
    for (int i = 0; i <= length; i++) {
        if (hex[length - i] > 47 && hex[length - i] < 58) {
            num = num + (hex[length - i] - 48) * base;
            base = base * 16;
        }
        else if (hex[length - i] > 64 && hex[length - i] < 91) {
            num = num + (hex[length - i] - 55) * base;
            base = base * 16;
        }
        else if (hex[length - i] > 96 && hex[length - i] < 123) {
            num = num + (hex[length - i] - 87) * base;
            base = base * 16;
        }
    }
    return num;
}
