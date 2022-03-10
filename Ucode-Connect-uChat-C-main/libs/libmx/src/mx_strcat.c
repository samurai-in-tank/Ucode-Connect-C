#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
    int length1 = mx_strlen(s1);
    int length2 = mx_strlen(s2);
    int i = length1;
    for (int j = 0; i < (length1 + length2); j++){
        s1[i] = s2[j];
        i++;
    }
    s1[i++] = '\0';
    return s1;
}
