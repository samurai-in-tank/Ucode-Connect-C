#include "libmx.h"

char *mx_strcpy(char *dst, const char *src) {
    int j = 0;
    for (int i = 0; src[i] != '\0'; i++) {
        dst[i] = src[i];
        j++;
    }
    dst[j] = '\0';
    return dst;
}
