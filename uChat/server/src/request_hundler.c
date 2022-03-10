#include "server.h"

static int check_input_data(char *username, char *server_password, char *password) {
    if (strlen(username) < 3) {
        return 1;
    }
    else if (strlen(username) > 32) {
        return 2;
    }
    for (int i = 0; username[i] != '\0'; i++) {
        if (!mx_isalpha(username[i]) && !mx_isdigit(username[i]) && !mx_isspace(username[i])) {
            return 3;
        }
    }
    /*for (vector_t *user_index = get_usernames(); user_index != NULL; user_index = user_index->next) {
        if (!strcmp((char *)user_index->data, username)) {
            return 4;
        }
    }*/
    if (strcmp(server_password, password)) {
        return 5;
    }
    return 0;
}

static void check_message(char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        if (message[i] == '`') {
            message[i] = '\'';
        }
    }
}

char *request_hundler(json_value *query, app_t *app, vector_t *chats_vector, char *server_name) {
    char *json_str = NULL;
    json_value *arr = json_array_new(0);
    if (app->type == CREATE_MESSAGE_QUERY) {
        char *token = query->u.array.values[1]->u.string.ptr;
        int type_message = query->u.array.values[2]->u.integer;
        int chat_id = query->u.array.values[3]->u.integer;
        char *username = query->u.array.values[4]->u.string.ptr;
        char *text = query->u.array.values[5]->u.string.ptr;
        char *for_user = query->u.array.values[6]->u.string.ptr;
        check_message(text);
        
        json_array_push(arr, json_integer_new(CREATE_MESSAGE_RESPONSE));
        json_array_push(arr, json_string_new(token));

        if (!strncmp(token, app->token, 5)) {
            json_array_push(arr, json_integer_new(0));
            time_t ti = time(NULL);
            insert_message(type_message, chat_id, username, app->user_icon, text, for_user, (long)ti);
            int message_id = get_last_message_id();
            json_array_push(arr, json_integer_new(message_id));
        }
        else {
            json_array_push(arr, json_integer_new(1));
        }
    }
    else if (app->type == LOGIN_QUERY) {
        char *username = query->u.array.values[1]->u.string.ptr;
        char *password = query->u.array.values[2]->u.string.ptr;
        int currentable_input_data = check_input_data(username, app->server_password, password);
        json_array_push(arr, json_integer_new(LOGIN_RESPONSE));
        json_array_push(arr, json_integer_new(currentable_input_data));
        int a = 0;

        if (currentable_input_data == 0) {
            insert_user(app->token, username, app->user_icon, 0);
            app->current_username = strdup(username);

            json_array_push(arr, json_string_new(app->token));
            json_array_push(arr, json_string_new(username));

            get_messages(arr, a, username);
            get_chats(arr, chats_vector);
            get_users_online(arr);

            app->last_message_id = get_last_message_id();
            json_array_push(arr, json_integer_new(app->user_icon));
            json_array_push(arr, json_string_new(server_name));
        }
    }
    else if (app->type == UPDATE_QUERY) {
        char *token = query->u.array.values[1]->u.string.ptr;
        char *username = strdup(query->u.array.values[2]->u.string.ptr);
        int user_icon = query->u.array.values[3]->u.integer;
        int chat_id = query->u.array.values[4]->u.integer;
        int error = check_input_data(username, "a", "a");

        if (strcmp(username, app->current_username) && error == 0) {
            update_user_username(username, app->current_username);
            app->current_username = username;
        }
        if (user_icon != app->user_icon) {
            update_user_icon(user_icon, app->current_username);
            app->user_icon = user_icon;
        }
        if (chat_id != app->current_chat) {
            update_user_chat(chat_id, app->current_username);
            app->current_chat = chat_id;
        }

        json_array_push(arr, json_integer_new(UPDATE_RESPONSE));
        json_array_push(arr, json_string_new(token));
        json_array_push(arr, json_integer_new(error));
        json_array_push(arr, json_string_new(app->current_username));
        json_array_push(arr, json_integer_new(app->user_icon));
        json_array_push(arr, json_integer_new(app->current_chat));

        get_messages(arr, app->last_message_id, app->current_username);
        app->last_message_id = get_last_message_id();
        get_users_online(arr);
    }
    else if (app->type == LOGOUT_QUERY) {
        remove_user(app->current_username);
        app->logout = true;
    }
    json_str = malloc(json_measure(arr));
    json_serialize(json_str, arr);
    json_value_free(arr);
    return json_str;
}
