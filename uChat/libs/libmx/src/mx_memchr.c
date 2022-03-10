#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    unsigned char *a = (unsigned char *)s;
    for (; n > 0; n--) {
        if (*a == (unsigned char)c) {
            return a;
        }
    }
    return NULL;
}
