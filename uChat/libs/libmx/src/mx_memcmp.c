#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    if (n == 0) {
        return 0;
    }
    const unsigned char *string1 = s1;
    const unsigned char *string2 = s2;
    unsigned int i = 0;
    for (;string1[i] == string2[i] && i != n; i++) {
        if (string1[i] == '\0' && string2[i] == '\0') {
            return 0;
        }
    }
    return string1[i] - string2[i];
}
