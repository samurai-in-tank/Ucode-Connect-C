#include "libmx.h"

char *mx_strjoin_free(char const *s1, char const *s2) {
    if (!s1 && !s2) {
        return NULL;
    }
    if (!s1 && s2) {
        return mx_strdup(s2);
    }
    if (s1 && !s2) {
        return mx_strdup(s1);
    }
    char *new = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
    new = mx_strcat(mx_strcpy(new, s1), s2);
    char *del = (char*)s1;
    mx_strdel(&del);
    return new;
}
