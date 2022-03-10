#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    if (!str || !sub) {
        return -1;
    }
    int count = 0;
    int len_str = mx_strlen(str);
    int len_sub = mx_strlen(sub);
    if (len_str >= len_sub) {
        while (*str) {
            if (!mx_strncmp((char *)str, (char *)sub, len_sub)) {
                count++;
            }
            str++;
        }
    }
    return count;
}
