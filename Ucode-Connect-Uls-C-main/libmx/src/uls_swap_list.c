#include "../inc/libmx.h"

void uls_swap_list(ls_list **bondOne, ls_list **bondTwo) {
    ls_list *temp = *bondOne;
    *bondOne = *bondTwo;
    *bondTwo = temp;
}
