
#include "server.h"

char *itoa(int num) {
    char *str = NULL;
    asprintf(&str, "%d", num);
    return str;
}

static void get_settings(server_t *server, json_value *main_object) {
    server->server_name = strdup(main_object->u.object.values[0].value->u.string.ptr);
    server->server_password = strdup(main_object->u.object.values[1].value->u.string.ptr);
    server->chats_vector = NULL;
    json_value *array_chats = main_object->u.object.values[2].value;
    int array_length = array_chats->u.array.length;
    for (int i = 0; i < array_length; i++) {
        json_value *json_chat = array_chats->u.array.values[i];
        chat_t *chat = (chat_t *)malloc(sizeof(chat_t));
        chat->id = json_chat->u.object.values[0].value->u.integer;
        chat->name = strdup(json_chat->u.object.values[1].value->u.string.ptr);
        chat->status = strdup(json_chat->u.object.values[2].value->u.string.ptr);
        chat->description = strdup(json_chat->u.object.values[3].value->u.string.ptr);
        chat->chat_icon = json_chat->u.object.values[4].value->u.integer;
        vector_push_back(&server->chats_vector, chat);
    }
    //write(1, "1", 1);
    json_value *main_mess = main_object->u.object.values[3].value;
    server->first_user_username = strdup(main_mess->u.object.values[0].value->u.string.ptr);
    server->first_user_text = strdup(main_mess->u.object.values[1].value->u.string.ptr);
}

static json_value *open_json() {
    char *file_name = "settings.json";
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

void get_settings_from_json(server_t *server) {
    json_value *j_value = open_json();
    //write(1, "1", 1);
    get_settings(server, j_value);
    //write(1, "1", 1);
    json_value_free(j_value);
}

int main(int argc, char **argv) {
    int listenfd = 0;
    int connfd = 0;
    pid_t pid;
    struct sockaddr_in serv_addr;

    if (argc < 2) {
        printf("nope\n");
        exit(1);
    }

    daemonizing();

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(listenfd, 10);

    server_t *server = (server_t *)malloc(sizeof(server_t));
    get_settings_from_json(server);
    //write(1, "1", 1);
    insert_message(1, 0, server->first_user_username, 0, server->first_user_text, "", time(NULL));

    while (1) {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        pid = fork();
        
        if (pid == 0) {
            //child
            app_t *app = (app_t *)malloc(sizeof(app_t));
            app->token = "token";
            app->server_password = server->server_password;
            app->last_message_id = 0;
            srand(time(NULL));
            app->user_icon = rand() % 10;
            app->current_chat = 0;
            app->logout = false;
            app->current_username = NULL;
            app->type = 0;
            while (1) {
                char len_buff[10];
                memset(len_buff, '\0', sizeof(len_buff));
                read(connfd, len_buff, sizeof(len_buff));

                char buff[atoi(len_buff)];
                memset(buff, '\0', atoi(len_buff));
                read(connfd, buff, sizeof(buff));

                json_char *j_char = (json_char *)buff;
                json_value *j_value = json_parse(j_char, sizeof(buff));
                app->type = j_value->u.array.values[0]->u.integer;

                char *json_str = request_hundler(j_value, app, server->chats_vector, server->server_name);
                
                memset(len_buff, '\0', sizeof(len_buff));
                char *len_json_str = itoa(strlen(json_str));
                for (int i = 0; len_json_str[i] != '\0'; i++) {
                    len_buff[i] = len_json_str[i];
                }
                
                write(connfd, len_buff, sizeof(len_buff));
                
                write(connfd, json_str, strlen(json_str));
                
                json_value_free(j_value);
                mx_strdel(&json_str);
                mx_strdel(&len_json_str);

                if (app->logout == true) {
                    break;
                }
            }
            free(app);
        }
        else if (pid > 0) {
            //master server
            printf("Created subserver for %d, pid: %d\n", connfd, pid);
            connfd = 0;
            pid = 0;
            continue;
        }
        else {
            exit(1);
        }
    }
    close(listenfd);
    return 0;
}
