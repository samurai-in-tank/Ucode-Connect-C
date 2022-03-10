#include "libmx.h"

int mx_get_substr_index(const char *str, const char* sub) {
    if (!str || !sub) {
        return -2;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        int count_sub = 0;
        if (str[i] == sub[count_sub]) {
            bool find = true;
            for (int j = i; sub[count_sub] != '\0'; j++) {
                if (str[j] != sub[count_sub]) {
                    find = false;
                    break;
                }
                count_sub++;
            }
            if (find == true) {
                return i;
            }
        }
    }
    return -1;
}
