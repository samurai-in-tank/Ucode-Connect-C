#include "libmx.h"

char *mx_itoa(int number) {
    int len = 0;
    int number2 = number;
	while (number2) {
		number2 /= 10;
		len++;
	}
	int a = number;
	char *res = NULL;
	res = mx_strnew(len);
	if (number == 0) {
        return mx_strcpy(res, "0");
    }
	if (number == -2147483648) {
        return mx_strcpy(res, "-2147483648");
    }
	a = number;
	for (int i = 0; i < len; i++) {
		if (a < 0) {
			res[len] = '-';
			a = -a;
		}
		res[i] = (a % 10) + '0';
		a /= 10;
	}
	for (int i = 0; i < len / 2; i++) {
	    int b = res[i];
	    res[i] = res[len - 1 - i];
	    res[len - 1 - i] = b;
	}
	return res;
}
