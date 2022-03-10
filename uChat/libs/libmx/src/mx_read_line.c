#include "libmx.h"

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    if (buf_size == 0) {
        return -2;
    }
    buf_size = 1;
    int count = 0;
    int num_bytes = 0;
    char *a = *lineptr;
    *lineptr = NULL;
    char *sym = mx_strnew(buf_size);
    while ((num_bytes = read(fd, sym, buf_size)) > 0) {
        if (mx_get_char_index(sym, delim) >= 0) {
            sym[mx_get_char_index(sym, delim)] = '\0';
            *lineptr = mx_strjoin_free(*lineptr, sym);
            count += mx_strlen(sym);
            free(sym);
            free(a);
            return count;
        }
        *lineptr = mx_strjoin_free(*lineptr, sym);
        count += num_bytes;
    }
    if (count == 0) {
        *lineptr = a;
        free(sym);
        if (num_bytes == -1) {
            return -2;
        }
        else {
            return -1;
        }
    }
    free(sym);
    return count;
}
