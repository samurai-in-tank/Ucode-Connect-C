#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int f = 0;
    int l = size - 1;
    while (f <= l) {
        int m = (f + l) / 2;
        if (mx_strcmp(arr[m], s) < 0) {
            f = m + 1;
            *count += 1;
        }
        else if (mx_strcmp(arr[m], s) > 0) {
            l = m - 1;
            *count += 1;
        }
        else {
            *count += 1;
            return m;
        }
    }
    *count = 0;
    return -1;
}
