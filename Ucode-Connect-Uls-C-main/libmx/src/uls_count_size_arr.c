#include "../inc/libmx.h"

int uls_count_size_arr(ls_list **disp) {
	int i = 0;

	while(disp[i])
		i++;
	return i;
}
