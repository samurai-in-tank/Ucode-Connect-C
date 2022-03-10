#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
	if (big_len <= 0 && little_len <= 0 && big_len < little_len) {
		return NULL;
	}
	unsigned char *basic = (unsigned char *)big;
	unsigned char *compared = (unsigned char *)little;
	while (*basic) {
		if (mx_memcmp(basic, compared, little_len - 1) == 0) {
		    return basic;
		}
		basic++;
	}
	return NULL;
}
