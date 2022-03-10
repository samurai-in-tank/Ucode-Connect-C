#include "libmx.h"

int mx_count_words(const char *str, char c) {
    if (str == NULL) {
        return -1;
    }
    bool is_word = false;
    int count = 0;
    int i = 0;
    while (str[i]) {
        if (str[i] == c) {
            is_word = false;
        }
        else if (is_word == false) {
            is_word = true;
            count++;
        }
        i++;
    }
    return count;
}
