#include "libmx.h"

int mx_sqrt(int x) {
    if (x == 1) {
        return 1;
    }
    if (x == 4) {
        return 2;
    }
    for (int i = 0; i < x / 2; i++) {
        int n = i * i;
        if (n > x) {
            return 0;
        }
        else if (n == x) {
            return i;
        }
    }
    return 0;
}
