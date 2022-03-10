#include "libmx.h"

char *mx_strjoin(const char *s1, const char *s2) {
    if (s1 == NULL && s2 == NULL) {
        return NULL;
    }
    else if (s1 == NULL) {
        return mx_strdup(s2);
    }
    else if (s2 == NULL) {
        return mx_strdup(s1);
    }
    else {
        char *a = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
        a = mx_strcpy(a, s1);
        a = mx_strcat(a, s2);
        return a;
    }
}
