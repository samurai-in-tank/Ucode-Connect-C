#include "cheers.h"

json_value *open_json() {
    char *file_name = "../vocabulary.json";
    FILE *file;
    struct stat file_status;
    int file_size;
    char *file_contents;
    json_char *json_str;
    json_value* j_value;

    if (stat(file_name, &file_status) != 0) {
        fprintf(stderr, "File %s not found\n", file_name);
        exit(0);
    }

    file_size = file_status.st_size;
    file_contents = (char *)malloc(file_status.st_size);
    if (file_contents == NULL) {
        fprintf(stderr, "Memory error: unable to allocate %d bytes\n", file_size);
        exit(0);
    }

    file = fopen(file_name, "rt");
    if (file == NULL) {
        fprintf(stderr, "Unable to open %s\n", file_name);
        fclose(file);
        free(file_contents);
        exit(0);
    }

    if (fread(file_contents, file_size, 1, file) != 1) {
        fprintf(stderr, "Unable to read content of %s\n", file_name);
        fclose(file);
        free(file_contents);
        exit(0);
    }

    fclose(file);

    json_str = (json_char *)file_contents;

    j_value = json_parse(json_str, file_size);

    if (j_value == NULL) {
        fprintf(stderr, "Unable to parse data\n");
        free(file_contents);
        exit(1);
    }

    free(file_contents);
    return j_value;
}
