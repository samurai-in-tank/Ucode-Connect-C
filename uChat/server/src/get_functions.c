#include "server.h"

void get_messages(json_value *arr, int message_id, char *username) {
    json_value *messages = json_array_push(arr, json_array_new(0));
    int last_message_id = get_last_message_id();

    printf("%d : %d\n", message_id, last_message_id);

    if (last_message_id > message_id) {
        for (int i = message_id + 1; i <= last_message_id; i++) {
            message_t *message_db = get_message(i);
            if (strcmp(message_db->for_user, "") == 0 || strcmp(message_db->for_user, username) == 0) {
                json_value *message_json = json_array_push(messages, json_array_new(0));
                json_array_push(message_json, json_integer_new(message_db->id));
                json_array_push(message_json, json_integer_new(message_db->type));
                json_array_push(message_json, json_integer_new(message_db->chat_id));
                json_array_push(message_json, json_string_new(message_db->username));
                json_array_push(message_json, json_integer_new(message_db->user_icon));
                json_array_push(message_json, json_string_new(message_db->text));
                json_array_push(message_json, json_boolean_new(strcmp(message_db->for_user, "") == 0 ? false : true));
                json_array_push(message_json, json_integer_new(message_db->datetime));
            }
        }
    }
}

void get_chats(json_value *arr, vector_t *chats_vector) {
    json_value *chats = json_array_push(arr, json_array_new(0));
    for (vector_t *chat_index = chats_vector; chat_index != NULL; chat_index = chat_index->next) {
        chat_t *chat_db = (chat_t *)chat_index->data;
        json_value *chat_json = json_array_push(chats, json_array_new(0));
        json_array_push(chat_json, json_integer_new(chat_db->id));
        json_array_push(chat_json, json_string_new(chat_db->name));
        json_array_push(chat_json, json_string_new(chat_db->status));
        json_array_push(chat_json, json_string_new(chat_db->description));
        json_array_push(chat_json, json_integer_new(chat_db->chat_icon));
    }
}

void get_users_online(json_value *arr) {
    json_value *users = json_array_push(arr, json_array_new(0));
    int last_user_id = get_last_user_id();
    for (int i = 1; i < last_user_id + 1; i++) {
        user_t *user = get_user_by_id(i);
        if (user != NULL) {
            json_value *user_json = json_array_push(users, json_array_new(0));
            json_array_push(user_json, json_string_new(user->username));
            json_array_push(user_json, json_integer_new(user->current_chat_id));
        }   
    }
}
