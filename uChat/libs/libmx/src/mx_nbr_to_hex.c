#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    unsigned long n = nbr;
    int length = 0;
    int r = 0;
    while (nbr != 0) {
        nbr /= 16;
        length++;
    }
    if (length == 0) {
        return "0";
    }
    char *hex_num = (char *)malloc(length + 1);
    if (hex_num == NULL) {
        return NULL;
    }
    for (int i = 0; i < length + 1; i++) {
        hex_num[i] = '\0';
    }
    for (int i = length - 1; i >= 0; i--) {
        r = n % 16;
        if (r < 10) {
            hex_num[i] = r + 48;
        }
        else {
            hex_num[i] = r + 87;
        }
        n /= 16;
    }
    return hex_num;
}
