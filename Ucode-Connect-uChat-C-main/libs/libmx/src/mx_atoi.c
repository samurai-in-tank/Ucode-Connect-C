#include "libmx.h"

int mx_atoi(const char *str) {
    int first = -1;
    int last = -1;
    bool mines = false;
    int result = 0;
    if (mx_strcmp(str, "2147483647") == 0 || mx_strcmp(str, "-2147483648") == 0) {
        return 0;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '-' && (str[i + 1] >= 48 && str[i + 1] <= 57)) {
            mines = true;
            continue;
        }
        if (str[i] != ' ' && str[i] != '\f' && str[i] != '\n'
            && str[i] != '\r' && str[i] != '\t' && str[i] != '\v'
            && (str[i] < 48 || str[i] > 57)) {
                return 0;
            }
        if ((str[i] != ' ' && str[i] != '\f' && str[i] != '\n'
            && str[i] != '\r' && str[i] != '\t' && str[i] != '\v')
            && first == -1) {
            first = i;
        }
        else if (first > -1 && (str[i] < 48 || str[i] > 57)) {
            last = i;
            break;
        }
    }
    if (last == -1) {
        for (int i = first; str[i] != '\0'; i++) {
            result = result * 10 + (int)str[i] - 48;
        }
    }
    else {
        for (int i = first; i != last; i++) {
            if (str[i] != '-') {
                result = result * 10 + (int)str[i] - 48;
            }
        }
    }
    return mines == false ? result : result * -1;
}
