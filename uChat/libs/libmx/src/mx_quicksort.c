#include "libmx.h"

int mx_quicksort(char **arr, int left, int right) {
    if (!arr) {
        return -1;
    }
    int i = 0;
    if (left < right) {
        int first = left;
        int last = right;
        char *pivot = arr[(first + last) / 2];
        while (first <= last) {
            while (mx_strlen(arr[first]) < mx_strlen(pivot)) {
                first++;
            }
            while (mx_strlen(arr[last]) > mx_strlen(pivot)) {
                last--;
            }
            if (first <= last) {
                if (mx_strlen(arr[last]) != mx_strlen(arr[first])) {
                    char *a = arr[first];
                    arr[first] = arr[last];
                    arr[last] = a;
                    i++;
                }
                last--;
                first++;
            }
        }
        i += mx_quicksort(arr, left, last);
        i += mx_quicksort(arr, first, right);
    }
    return i;
}
