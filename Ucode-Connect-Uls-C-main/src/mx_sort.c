#include "uls.h"

void mx_sort(ls_list ***disp, st_fl *fl) {
	ls_list **bond = *disp;
	int size = uls_count_size_arr(bond);

	for (int i = 0; i < size; i++) {
		for (int k = i + 1; k < size; k++) {
            if (bond[i]->err != NULL) {
                if (mx_strcmp(bond[i]->name, bond[k]->name) == 1)
                    uls_swap_list(&(bond[i]), &(bond[k]));
            }
            else if (uls_cmp_sort(bond[i], bond[k], fl) == fl->r) {
                uls_swap_list(&(bond[i]), &(bond[k]));
			}
		}
	}
}
