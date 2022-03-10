#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    int len1 = mx_strlen(needle);
    int len2 = mx_strlen(haystack);
    for (int i = 0; i < len1; i++) {
        char *a = mx_strchr(haystack, haystack[0]);
        if (mx_strncmp(a, needle, len2) == 0) {
            return (char *)haystack;
        }
        haystack++;
    }
    return NULL;
}
