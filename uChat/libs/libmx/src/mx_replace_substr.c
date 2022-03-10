#include "libmx.h"

char *replacing(const char *str, const char *sub, const char *replace, int difference, int i) {
    bool is_replace = false;
    char *str_copy = mx_strnew(mx_strlen(str) + difference);
    const char *str2 = str;
    int ind = mx_get_substr_index(str2, sub);
    for (int j = 0; j < mx_strlen(str) + difference * (i + 1); j++) {
        if (j == ind) {
            is_replace = true;
            str_copy[j] = replace[j - ind];
        }
        else if (j == ind + mx_strlen(replace)) {
            is_replace = false;
            str_copy[j] = str[j + difference];
        }
        else if (is_replace == true) {
            str_copy[j] = replace[j - ind];
        }
        else if (is_replace == false && j > ind) {
            str_copy[j] = str[j + difference];
        }
        else {
            str_copy[j] = str[j];
        }
    }
    return str_copy;
}

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (!str || !sub || !replace || mx_strlen(sub) > mx_strlen(str)) {
        return NULL;
    }
    int count_substr = mx_count_substr(str, sub);
    int difference = mx_strlen(replace) - mx_strlen(sub);
    char *str2 = mx_strnew(mx_strlen(str) + difference);
    if (count_substr > 0) {
        const char *str3 = str;
        str2 = replacing(str3, sub, replace, difference, 0);
    }
    for (int i = 1; i < count_substr; i++) {
        str2 = replacing(str2, sub, replace, difference, i);
    }
    return str2;
}
