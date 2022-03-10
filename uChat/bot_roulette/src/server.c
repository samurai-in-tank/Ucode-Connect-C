#include "cheers.h"

void send_query(json_value *arr, int sockfd) {
    char *json_str = malloc(json_measure(arr));
    json_serialize(json_str, arr);

    char len_buff[10];
    memset(len_buff, '\0', sizeof(len_buff));
    char *len_json_str = itoa(strlen(json_str));
    for (int i = 0; len_json_str[i] != '\0'; i++) {
        len_buff[i] = len_json_str[i];
    }

    write(sockfd, len_buff, sizeof(len_buff));

    write(sockfd, json_str, strlen(json_str));

    mx_strdel(&json_str);
    mx_strdel(&len_json_str);
}

json_value *get_response(int sockfd) {
    char len_buff[10];
    memset(len_buff, '\0', sizeof(len_buff));
    read(sockfd, len_buff, sizeof(len_buff));

    char buff[atoi(len_buff)];
    read(sockfd, buff, sizeof(buff));

    write(1, buff, sizeof(buff));
    json_char *j_char = (json_char *)buff;

    //printf("%s\n", buff);

    return json_parse(j_char, sizeof(buff));
}

void receive_response(app_t *app) {
    json_value *response = NULL;
    if (app->type == CREATE_MESSAGE_RESPONSE) {
        response = get_response(app->sockfd);
        
        if (response->u.array.values[2]->u.integer > 0) {
            printf("HUI TEBE\n");
        }
    }
    else if (app->type == LOGIN_RESPONSE) {
        response = get_response(app->sockfd);

        int error = response->u.array.values[1]->u.integer;

        if (error == 0) {
            if (!app->token) {
                free(app->token);
            }
            if (!app->username) {
                free(app->username);
            }
            app->token = strdup(response->u.array.values[2]->u.string.ptr);
            app->username = strdup(response->u.array.values[3]->u.string.ptr);

            get_messages(app, response, 4);
            //printf("\n");
            get_chats(app, response, 5);
            //printf("\n");
            get_user_online(app, response, 6);
            //printf("\n");

            app->user_icon = response->u.array.values[7]->u.integer;                 
        }
        else {
            printf("Incorrect data");
        }
    }
    else if (app->type == UPDATE_RESPONSE) {       
        response = get_response(app->sockfd);
        if (response->u.array.values[2]->u.integer > 0) {
            printf("HUI TEBE\n");
        }
        else {
            app->username = strdup(response->u.array.values[3]->u.string.ptr);
            app->user_icon = response->u.array.values[4]->u.integer;
            app->chat_id = response->u.array.values[5]->u.integer;
            get_messages(app, response, 6);
            //printf("\n");
            get_user_online(app, response, 7);
            //printf("\n");
        }
    }
    json_value_free(response);
}

void get_messages(app_t *app, json_value *response, int num_array) {
    json_value *array_messages = response->u.array.values[num_array];
    int length = array_messages->u.array.length;

    for (int x = 0; x < length; x++) {
        json_value *array_message = array_messages->u.array.values[x];
        message_t *message = (message_t *)malloc(sizeof(message_t));
        message->id = array_message->u.array.values[0]->u.integer;
        message->type = array_message->u.array.values[1]->u.integer;
        message->chat_id = array_message->u.array.values[2]->u.integer;
        message->username = strdup(array_message->u.array.values[3]->u.string.ptr);
        message->user_icon = array_message->u.array.values[4]->u.integer;
        message->text = strdup(array_message->u.array.values[5]->u.string.ptr);
        message->is_only_for_me = array_message->u.array.values[6]->u.integer;
        message->datetime = array_message->u.array.values[7]->u.integer;
        vector_push_back(&app->messages, message);
        //printf("%s\n", message->text);
    }
}

void get_chats(app_t *app, json_value *response, int num_array) {
    json_value *array_chats = response->u.array.values[num_array];
    int length = array_chats->u.array.length;
    for (int x = 0; x < length; x++) {
        json_value *array_chat = array_chats->u.array.values[x];
        chat_t *chat = (chat_t *)malloc(sizeof(chat_t));
        chat->id = array_chat->u.array.values[0]->u.integer;
        chat->name = strdup(array_chat->u.array.values[1]->u.string.ptr);
        chat->status = strdup(array_chat->u.array.values[2]->u.string.ptr);
        chat->description = strdup(array_chat->u.array.values[3]->u.string.ptr);
        chat->chat_icon = array_chat->u.array.values[4]->u.integer;
        vector_push_back(&app->chats, chat);
        //printf("%s\n", chat->name);
    }
}

void get_user_online(app_t *app, json_value *response, int num_array) {
    json_value *array_users = response->u.array.values[num_array];
    int length = array_users->u.array.length;
    for (int x = 0; x < length; x++) {
        json_value *array_user = array_users->u.array.values[x];
        user_t *user = (user_t *)malloc(sizeof(user_t));
        user->username = strdup(array_user->u.array.values[0]->u.string.ptr);
        user->current_chat_online = array_user->u.array.values[1]->u.integer;
        vector_push_back(&app->users, user);
    }
}

void send_login(app_t *app, char *username, char *server_password) {
    json_value *new = json_array_new(0);
    json_array_push(new, json_integer_new(LOGIN_QUERY));
    json_array_push(new, json_string_new(username));
    json_array_push(new, json_string_new(server_password));

    send_query(new, app->sockfd);

    json_value_free(new);
}

void send_message(app_t *app, int type_message, const char *text, char *for_user) {
    json_value *new = json_array_new(0);
    json_array_push(new, json_integer_new(CREATE_MESSAGE_QUERY));
    json_array_push(new, json_string_new(app->token));
    json_array_push(new, json_integer_new(type_message));
    json_array_push(new, json_integer_new(app->chat_id));
    json_array_push(new, json_string_new(app->username));
    json_array_push(new, json_string_new(text));
    json_array_push(new, json_string_new(for_user));
    
    send_query(new, app->sockfd);

    json_value_free(new);
}

void send_update(app_t *app) {
    json_value *new = json_array_new(0);
    json_array_push(new, json_integer_new(UPDATE_QUERY));
    json_array_push(new, json_string_new(app->token));
    json_array_push(new, json_string_new(app->username));
    json_array_push(new, json_integer_new(app->user_icon));
    json_array_push(new, json_integer_new(app->chat_id));
    
    send_query(new, app->sockfd);

    json_value_free(new);
}

void send_logout(app_t *app) {
    json_value *new = json_array_new(0);
    json_array_push(new, json_integer_new(LOGOUT_QUERY));
    json_array_push(new, json_string_new(app->token));

    send_query(new, app->sockfd);

    json_value_free(new);
}
