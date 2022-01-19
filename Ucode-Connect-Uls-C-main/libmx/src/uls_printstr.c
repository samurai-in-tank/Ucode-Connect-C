#include "../inc/libmx.h"

void uls_printstr(const char *s) {
	write(1, s, mx_strlen(s));
}
