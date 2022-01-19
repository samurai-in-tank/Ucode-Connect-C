#include "../inc/libmx.h"

ls_list *uls_create_li_node(char *data) {
    ls_list *node = (ls_list *)malloc(1 * sizeof(ls_list));
//выделяет память исходя из размера списка tli
    node->name = mx_strdup(data);
    //дублирует data   в name в структуру ls_list
    node->path = mx_strdup(data);
    //дублирует data   в path в структуру ls_list
    node->err = NULL;
    if (lstat(data, &(node->info)) == -1)// но в случае символьных сылок она возвращает информацию о самой ссылке, а не о файле, на который она указывает..
        node->err = mx_strdup(strerror(errno));	
        //если ссылки не существует то ощибка
    node->open = NULL;
    return node;
}
