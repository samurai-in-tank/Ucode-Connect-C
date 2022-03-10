#include "libmx.h"

int count_letters(const char *s, char c) {
	int i = 0;
	while (s[i] != c && s[i]) {
        i++;
    }
	return i;
}

char **mx_strsplit(const char *s, char c) {
    if (!s) {
        return NULL;
    }
    int len_word = 0;
    int i = 0;
    char **arr = (char **)malloc((mx_count_words(s, c) + 1) * sizeof(char *));
    while ((*s) && (*s != '\0')) {
        if (*s != c) {
            len_word = count_letters(s, c);
            arr[i] = mx_strndup(s, len_word);
            s += len_word;
            i++;
            continue;
        }
        s++;
    }
    arr[i] = NULL;
    return arr;
}
