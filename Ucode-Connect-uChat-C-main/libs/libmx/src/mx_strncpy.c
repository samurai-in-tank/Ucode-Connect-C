#include "libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
    if (len < 1) {
        return dst;
    }
    int i = 0;
    for (;src[i] != '\0' && len > 0; i++) {
        dst[i] = src[i];
        len--;
    }
    while (len > 0) {
        dst[i] = 0;
        i++;
        len--;
    }
    return dst;
}
