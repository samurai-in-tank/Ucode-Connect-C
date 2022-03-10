#include "libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    size_t len = mx_strlen(s1);
    if (n < len) {
        len = n;
    }
    char *copy = mx_strnew(len);
    mx_strncpy(copy, s1, len);
    return copy;
}
