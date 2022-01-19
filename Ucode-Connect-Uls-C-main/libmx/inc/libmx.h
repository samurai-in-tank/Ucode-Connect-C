#ifndef LIBMX_H
#define LIBMX_H

#include "string.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <pwd.h>
#include <sys/xattr.h>
#include <grp.h>
#include <sys/acl.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <time.h>
#include <malloc/malloc.h>

#define LS_IS_BLK(mode) (((mode) & S_IFMT) == S_IFBLK)
#define LS_IS_CHR(mode) (((mode) & S_IFMT) == S_IFCHR)
#define LS_IS_DIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#define LS_IS_LNK(mode) (((mode) & S_IFMT) == S_IFLNK)
#define LS_IS_SOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)
#define LS_IS_FIFO(mode) (((mode) & S_IFMT) == S_IFIFO)
#define LS_IS_WHT(mode) (((mode) & S_IFMT) == S_IFWHT)
#define LS_IS_EXEC(mode) ((mode) & S_IXUSR)

#define COLOR_RED        "\x1b[31m"
#define COL_RESETs      "\x1b[0m"

//MY FUNCTION PACK
int mx_strncmp(const char *s1, const char *s2, int n);
char *mx_strchr(const char *s, int c);
bool mx_isspace(char c);
void mx_printerr(const char *s);
bool mx_isdigit(int c);
bool mx_isalpha(int c);

//UTILS PACK
void mx_printchar(char c);
void mx_print_unicode(wchar_t c);
void mx_printstr(const char *s);
void mx_print_strarr(char **arr, const char *delim);
void mx_printint(int n);
double mx_pow(double n, unsigned int pow);
int mx_sqrt(int x);
char *mx_nbr_to_hex(unsigned long nbr);
unsigned long mx_hex_to_nbr(const char *hex);
char *mx_itoa(int number);
void mx_foreach(const int *arr, int size, void (*f)(int));
int mx_binary_search(char **arr, int size, const char *s, int *count);
int mx_bubble_sort(char **arr, int size);
int mx_quicksort(char **arr, int left, int right);

//STRING PACK
int mx_strlen(const char *s);
void mx_swap_char(char *s1, char *s2);
void mx_str_reverse(char *s);
void mx_strdel(char **str);
void mx_del_strarr(char ***arr);
int mx_get_char_index(const char *str, char c);
char *mx_strdup(const char *s1);
char *mx_strndup(const char *s1, size_t n);
char *mx_strcpy(char *dst, const char *src);
char *mx_strncpy(char *dst, const char *src, int len);
int mx_strcmp(const char *s1, const char *s2);
char *mx_strcat(char *restrict s1, const char *restrict s2);
char *mx_strstr(const char *haystack, const char *needle);
int mx_get_substr_index(const char *str, const char *sub);
int mx_count_substr(const char *str, const char *sub);
int mx_count_words(const char *str, char c);
char *mx_strnew(const int size);
char *mx_strtrim(const char *str);
char *mx_del_extra_spaces(const char *str);
char **mx_strsplit(const char *s, char c);
char *mx_strjoin(const char *s1, const char *s2);
char *mx_file_to_str(const char *file);
char *mx_replace_substr(const char *str, const char *sub, const char *replace);
int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd);

//MEMORY PACK
void *mx_memset(void *b, int c, size_t len);
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);
void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n);
int mx_memcmp(const void *s1, const void *s2, size_t n);
void *mx_memchr(const void *s, int c, size_t n);
void *mx_memrchr(const void *s, int c, size_t n);
void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len);
void *mx_memmove(void *dst, const void *src, size_t len);
void *mx_realloc(void *ptr, size_t size);

//LIST PACK
typedef struct s_list {
    void *data;
    struct s_list*next;
}           t_list;

t_list *mx_create_node(void *data);
void mx_push_front(t_list **list, void *data);
void mx_push_back(t_list **list, void *data);
void mx_pop_front(t_list **head);
void mx_pop_back(t_list **head);
int mx_list_size(t_list *list);
t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *));

//STRUCTs  for ULS
typedef struct fl {
    int l;
    int C;
    int x;
    int R;
    int r;
    int t;
    int u;
    int c;
    int S;
    int a;
    int A;
    int fr;
    int m;
    int fl;
    int G;
    int T;
    int g;
    int o;
    int ex;
}   st_fl;

typedef struct s_sz {
    int lnk;
    int sz;
    int group;
    int usr;
    bool is_dev;
}   ls_size;

typedef struct s_li {
    char *name;
    char *path;
    char *err;
    struct stat info;
    struct s_li **open;
}   ls_list;

typedef struct n_type {
    int n_f;
    int n_d;
    int n_e;
    int i;
}   ls_types;

//ULS PACK
char mx_check_per(ls_list *print);
void mx_del_arr_arr(ls_list ***args);
char mx_get_file_acl(ls_list *print);
void mx_get_group_name(ls_list *print, int group);
void mx_get_user_name(ls_list *print, int usr);
void mx_join(char **res, char *s2);
int mx_max_len_n_g(ls_list **names);
void mx_out_put_menu(ls_list ***names, st_fl *fl, int flag);
void mx_print_lnk(ls_list *print, ls_size *size);
void mx_print_spaces_g(int len, int maxlen);
void mx_print_tab(int len, int maxlen);
void uls_add_flags(st_fl **fl, char flag);
int uls_check_a(char *name, st_fl *fl);
char uls_check_chmode_1(char chmod);
char uls_check_chmode_2(char *chmod);
bool uls_check_device(ls_list **names, ls_size *size);
char *uls_check_group(ls_list *total);
char *uls_check_pw(ls_list *total);
int uls_cmp_sort_1(ls_list *first, ls_list *second, st_fl *fl);
int uls_cmp_sort_2(ls_list *first, ls_list *second, st_fl *fl);
int uls_cmp_sort(ls_list *first, ls_list *second, st_fl *fl);
int uls_count_read(ls_list **arg, st_fl *fl);
int uls_count_size_arr(ls_list **disp);
void uls_count_size_st_size(ls_size *size, ls_list *total);
void uls_create_fde_apgread(ls_list ***files, ls_list ***dirs, ls_list ***errors, ls_list ***args);
void uls_create_FDE(ls_list ***dirs, ls_list ***args);
ls_list *uls_create_file_node_for_get_file(ls_list *arg);
ls_list *uls_create_file_node(ls_list *arg);
ls_list *uls_create_he_node(char *name, char *path);
ls_list *uls_create_li_node(char *data);
ls_list **uls_create_list(char **name, int count);
ls_types *uls_create_num();
void uls_del_li_array(ls_list ***args, ls_list **dirs);
void uls_error_flag(st_fl **fl, char flag);
void uls_fdir(ls_list **args, ls_types *num, ls_list ***files, ls_list ***dirs);
st_fl *uls_get_flags(char *argv[], int *i);
char *uls_get_major(ls_list *print);
char *uls_get_minor(ls_list *print);
int uls_max_len_names(ls_list **names);
char *uls_minor_to_hex(char *minor);
char **uls_names_for_get(int argc, char **argv, int i, int *count);
void uls_nulloutput(st_fl **fl);
void uls_open_dir(ls_list ***args, st_fl *fl);
void uls_out_put_err_open(ls_list **args, st_fl *fl);
void uls_out_put(ls_list **names, st_fl *fl);
void uls_print_cols_x(ls_list **names, int rows, int cols, int maxlen);
void uls_print_cols(ls_list **names, int rows, int num, int maxlen);
void uls_print_duo_cases(ls_list *print, ls_size *size);
int uls_print_frst(ls_list *args);
void uls_print_link_and_color(ls_list *print, st_fl *fl);
void uls_print_name(ls_list *args);
void uls_print_names_m(ls_list **names, int wincol, st_fl *fl);
void uls_print_names_x(ls_list **names, int maxlen, int wincol);
void uls_print_names(ls_list **names, int maxlen, int wincol);
int uls_print_sec(ls_list *args);
void uls_print_spaces(int size);
void uls_printcols_c(ls_list **names, int rows, int num, int maxlen);
void uls_printcols_x(ls_list **names, int rows, int cols, int maxlen);
void uls_printn_m(int *len);
void uls_printnames_g(ls_list **names, int maxlen, int wincol, st_fl *fl);
void uls_printrow_g(ls_list **names, int maxlen);
void uls_printstr(const char *s);
void uls_size_zero_st_size(ls_size *size);
void uls_swap_list(ls_list **bondOne, ls_list **bondTwo);
void mx_printcharerr(char c);

//in ULS functions
void mx_output_del_files(ls_list ***args, st_fl *fl);
void mx_edit_time(ls_list *print, char *t, st_fl *fl);
void mx_long_out(ls_list **names, st_fl *fl, int flag);
ls_list **mx_get_files(ls_list ***args, st_fl *fl);
ls_list **mx_get_names(int argc, char **argv, int i);
void mx_opendir(ls_list ***args, st_fl *fl);
void mx_output_c(ls_list **names);
void mx_output_g(ls_list **names, st_fl *fl);
void mx_output_m(ls_list **names, st_fl *fl);
void mx_output_x(ls_list **names);
void mx_out_put_all(ls_list ***args, st_fl *fl);
void mx_print_all(ls_list *print, ls_size *size, st_fl *fl);
void mx_print_per(ls_list *print);
void mx_print_symblink(ls_list *print);
void mx_print_sz(ls_list *print, ls_size *size);
void mx_out_err(ls_list ***error, st_fl *fl);
void mx_printstr_g(ls_list *args);
void mx_sort(ls_list ***disp, st_fl *fl);

#endif

