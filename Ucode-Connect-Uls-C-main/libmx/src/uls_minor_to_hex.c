#include "../inc/libmx.h"

char *uls_minor_to_hex(char *minor) {
    char *hex_minor = mx_strdup("0x00000000");

    mx_strcpy(hex_minor + (10 - mx_strlen(minor)), minor);
    mx_strdel(&minor);
    return hex_minor;
}
