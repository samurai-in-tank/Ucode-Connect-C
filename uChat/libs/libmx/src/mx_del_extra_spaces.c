#include "libmx.h"

char *mx_del_extra_spaces(const char *str) {
    if (!str) {
        return NULL;
    }
    char *str2 = mx_strnew(mx_strlen(str));
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!mx_isspace(str[i])) {
            str2[j] = str[i];
            j++;
        }
        if (!mx_isspace(str[i]) && mx_isspace(str[i + 1])) {
            str2[j] = ' ';
            j++;
        }
    }
    char *a = mx_strtrim(str2);
    mx_strdel(&str2);
    return a;
}
