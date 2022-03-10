#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    unsigned char *a = malloc(len);
	a = mx_memcpy(a, src, len);
	dst = mx_memcpy(dst, a, len);
	free(a);
	return dst;
}
