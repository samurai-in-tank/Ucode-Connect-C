#include "server.h"

// Проверяем действительно ли юзер, запрашивающий данные, является участником чата
/*bool check_user(int user_id, int chat_id) {
    char *sql_query = NULL;
    char *sql_pattern = "SELECT EXISTS (SELECT id FROM chat_relation WHERE user_id=(%d) chat_id=(%d));";
    asprintf(&sql_query, sql_pattern, user_id, chat_id);
    vector_t *exit = query_db(sql_query, 1);
    int result = atoi(exit->data);
    mx_strdel(&sql_query);
    vector_free(&exit);
    return result == 0 ? false : true;
}

bool is_user(char *username) { // work
    char *sql_query = NULL;
    char *sql_pattern = "SELECT EXISTS (SELECT id FROM user WHERE username=('%s'));";
    asprintf(&sql_query, sql_pattern, username);
    vector_t *exit = query_db(sql_query, 1);
    int result = atoi(exit->data);
    vector_free(&exit);
    mx_strdel(&sql_query);
    return result == 0 ? false : true;
}*/

void insert_user(char *token, char *username, int user_icon, int chat_id) { // work
    char *sql_query = NULL;
    char *sql_pattern = "INSERT INTO user (token, username, user_icon, chat_id) VALUES ('%s', '%s', %d, %d);";
    asprintf(&sql_query, sql_pattern, token, username, user_icon, chat_id);
    query_db(sql_query, 2);
    mx_strdel(&sql_query);
}

/*int get_last_chat_id(void) {
    char *sql_query = "SELECT id FROM chat ORDER BY id DESC;";
    vector_t *list = query_db(sql_query, 1);
    mx_strdel(&sql_query);
    int i = atoi(list->data);
    vector_free(&list);
    return i;
}

int insert_chat(char *title, char *subscribe, int active_game, int type, int user_id) { //work
    char *sql_query = NULL;
    char *sql_pattern = "INSERT INTO chat (title, subscribe, active_game, type) VALUES ('%s', '%s', %d, %d);";
    asprintf(&sql_query, sql_pattern, title, subscribe, active_game, type);
    query_db(sql_query, 2);
    int chat_id = get_last_chat_id();
    insert_chat_reletion(user_id, chat_id, true);
    mx_strdel(&sql_query);
    return chat_id;
}*/

void insert_message(int type, int chat_id, char *username, int user_icon, char *text, char *for_user, long int datetime) { //work
    char *sql_query = NULL;
    char *sql_pattern = "INSERT INTO message (type, chat_id, username, user_icon, text, for_user, datetime) VALUES (%d, %d, '%s', %d, '%s', '%s', %ld);";
    asprintf(&sql_query, sql_pattern, type, chat_id, username, user_icon, text, for_user, datetime);
    query_db(sql_query, 2);
    mx_strdel(&sql_query);
}

/*void insert_chat_reletion(int user_id, int chat_id, bool is_admin) { //work
    char *sql_query = NULL;
    char *sql_pattern = is_admin ? "INSERT INTO chat_relation (user_id, chat_id, 1) VALUES (%d, %d);" : "INSERT INTO chat_relation (user_id, chat_id, 0) VALUES (%d, %d);";
    asprintf(&sql_query, sql_pattern, user_id, chat_id);
    query_db(sql_query, 2);
    mx_strdel(&sql_query);
}*/

message_t *get_message(int message_id) { //work
    char *sql_query = NULL;
    char *sql_pattern = "SELECT type, chat_id, username, user_icon, text, for_user, datetime FROM message WHERE id=(%d);";
    asprintf(&sql_query, sql_pattern, message_id);
    vector_t *list = query_db(sql_query, 1);
    mx_strdel(&sql_query);
    message_t *message = (message_t *)malloc(sizeof(message_t));
    message->id = message_id;
    message->type = atoi((char *)list->data);
    message->chat_id = atoi((char *)vector_get(&list, 1)->data);
    message->username = (char *)vector_get(&list, 2)->data;
    message->user_icon = atoi((char *)vector_get(&list, 3)->data);
    message->text = (char *)vector_get(&list, 4)->data;
    message->for_user = (char *)vector_get(&list, 5)->data;
    message->datetime = atoi((char *)vector_get(&list, 6)->data);
    return message;
}

vector_t *get_usernames(void) {
    char *sql_query = "SELECT username FROM user;";
    vector_t *list = query_db(sql_query, 1);
    return list;
}

user_t *get_user_by_id(int user_id) { // work
    char *sql_query = NULL;
    char *sql_pattern = "SELECT token, username, user_icon, chat_id FROM user WHERE id=(%d);";
    asprintf(&sql_query, sql_pattern, user_id);
    vector_t *list = query_db(sql_query, 1);
    mx_strdel(&sql_query);
    user_t *user = NULL;
    if (list != NULL) {
        user = (user_t *)malloc(sizeof(user_t));
        user->id = user_id;
        user->token = (char *)list->data;
        user->username = (char *)vector_get(&list, 1)->data;
        user->user_icon = atoi((char *)vector_get(&list, 2));
        user->current_chat_id = atoi((char *)vector_get(&list, 3));
    }
    return user;
}

/*user_t *get_user_by_username_and_password(char *username, char *password) { // work
    char *sql_query = NULL;
    char *sql_pattern = "SELECT id, name, online FROM user WHERE username=('%s') AND password=('%s');";
    asprintf(&sql_query, sql_pattern, username, password);
    vector_t *list = query_db(sql_query, 1);
    mx_strdel(&sql_query);
    user_t *user = (user_t *)malloc(sizeof(user_t));
    user->id = (int)list->data;
    user->username = username;
    user->name = vector_get(&list, 1)->data;
    user->password = password;
    user->online = (bool)vector_get(&list, 2)->data;
    return user;
}*/

int get_last_message_id() {
    char *sql_query = "SELECT id FROM message ORDER BY id DESC;";
    vector_t *list = query_db(sql_query, 1);
    int i = -1;
    if (list) {
        i = atoi((char *)list->data);
    }
    vector_free(&list);
    return i;
}

/*int get_next_message_id(int chat_id, int last_message_id) {
    char *sql_query = NULL;
    char *sql_pattern = "SELECT id FROM message WHERE chat_id=(%d) AND id > (%d);";
    asprintf(&sql_query, sql_pattern, chat_id, last_message_id);
    vector_t *list = query_db(sql_query, 1);
    mx_strdel(&sql_query);
    int i = -1;
    if (list) {
        i = atoi((char *)list->data);
    }
    vector_free(&list);
    return i;
}*/

int get_last_user_id(void) {
    char *sql_query = "SELECT id FROM user ORDER BY id DESC;";
    vector_t *list = query_db(sql_query, 1);
    int i = atoi(list->data);
    vector_free(&list);
    return i;
}

/*int get_last_chat_id(void) {
    char *sql_query = NULL;
    char *sql_pattern = "SELECT id FROM chat ORDER BY id DESC;";
    asprintf(&sql_query, sql_pattern);
    vector_t *list = query_db(sql_query, 1);
    mx_strdel(&sql_query);
    int i = atoi(list->data);
    vector_free(&list);
    return i;
}

chat_t *get_chat(int chat_id) { //work
    char *sql_query = NULL;
    char *sql_pattern = "SELECT title, subscribe, active_game, type FROM chat WHERE id=(%d);";
    asprintf(&sql_query, sql_pattern, chat_id);
    vector_t *list = query_db(sql_query, 1);
    char *sql_query2 = NULL;
    char *sql_pattern2 = "SELECT user_id FROM chat_relation WHERE chat_id=(%d);";
    asprintf(&sql_query2, sql_pattern2, chat_id);
    chat_t *chat = (chat_t *)malloc(sizeof(chat_t));
    chat->id = chat_id;
    chat->name = (char *)list->data;
    chat->subscribe = (char *)vector_get(&list, 1)->data;
    chat->active_game = (int)vector_get(&list, 2)->data;
    chat->type = (int)vector_get(&list, 3)->data;
    chat->users_id = query_db(sql_query2, 1);
    mx_strdel(&sql_query);
    mx_strdel(&sql_query2);
    return chat;
}

int get_user_id(char *username) { // work
    char *sql_query = NULL;
    char *sql_pattern = "SELECT id FROM user WHERE username=('%s');";
    asprintf(&sql_query, sql_pattern, username);
    vector_t *list = query_db(sql_query, 1);
    int i = atoi(list->data);
    vector_free(&list);
    return i;
}

void remove_chat(int chat_id) {
    char *sql_query = NULL;
    char *sql_pattern = "DELETE FROM chat WHERE id=(%d);";
    asprintf(&sql_query, sql_pattern, chat_id);
    query_db(sql_query, 2);
    mx_strdel(&sql_query);
}

void remove_chat_reletion(int user_id, int chat_id) {
    char *sql_query;
    char *sql_pattern = "DELETE FROM chat_relation WHERE user_id=(%d) AND chat_id=(%d);";
    asprintf(&sql_query, sql_pattern, user_id, chat_id);
    query_db(sql_query, 2);
    mx_strdel(&sql_query);
}*/

void remove_user(char *username) {
    char *sql_query = NULL;
    char *sql_pattern = "DELETE FROM user WHERE username=('%s');";
    asprintf(&sql_query, sql_pattern, username);
    query_db(sql_query, 2);
    mx_strdel(&sql_query);
}

void update_user_username(char *new_username, char *username) { // work
    char *sql_query = NULL;
    char *sql_pattern = "UPDATE user SET username=('%s') WHERE username=('%s');";
    asprintf(&sql_query, sql_pattern, new_username, username);
    query_db(sql_query, 2);
    mx_strdel(&sql_query);
}

void update_user_icon(int new_user_icon, char *username) {
    char *sql_query = NULL;
    char *sql_pattern = "UPDATE user SET user_icon=(%d) WHERE username=('%s');";
    asprintf(&sql_query, sql_pattern, new_user_icon, username);
    query_db(sql_query, 2);
    mx_strdel(&sql_query);
}

void update_user_chat(int chat_id, char *username) {
    char *sql_query = NULL;
    char *sql_pattern = "UPDATE user SET chat_id=(%d) WHERE username=('%s');";
    asprintf(&sql_query, sql_pattern, chat_id, username);
    query_db(sql_query, 2);
    mx_strdel(&sql_query);
}

/*void update_user_name(char *name, int user_id) { // work
    char *sql_query = NULL;
    char *sql_pattern = "UPDATE user SET name=('%s'), WHERE id=(%d);";
    asprintf(&sql_query, sql_pattern, name, user_id);
    query_db(sql_query, 2);
    mx_strdel(&sql_query);
}

void update_user_password(char *password, int user_id) { // work
    char *sql_query = NULL;
    char *sql_pattern = "UPDATE user SET password=('%s'), WHERE id=(%d);";
    asprintf(&sql_query, sql_pattern, password, user_id);
    query_db(sql_query, 2);
    mx_strdel(&sql_query);
}

void update_user_online(bool is_online, int user_id) {
    char *sql_query = NULL;
    char *sql_pattern = is_online ? "UPDATE user SET online=(1) WHERE id=(%d);" : "UPDATE users SET online=(0) WHERE id=(%d);";
    asprintf(&sql_query, sql_pattern, user_id);
    query_db(sql_query, 2);
    mx_strdel(&sql_query);
}

void update_message(char *text, int message_id) {
    char *sql_query = NULL;
    char *sql_pattern = "UPDATE user SET text=('%s'), WHERE id=(%d);";
    asprintf(&sql_query, sql_pattern, text, message_id);
    query_db(sql_query, 2);
    mx_strdel(&sql_query);
}

void rename_chat(char *title, int chat_id) {
    char *sql_query = NULL;
    char *sql_pattern = "UPDATE chat SET title=('%s'), WHERE id=(%d);";
    asprintf(&sql_query, sql_pattern, title, chat_id);
    query_db(sql_query, 2);
    mx_strdel(&sql_query);
}

void drop_database(void) {
    char *sql_query = NULL;
    char *sql_pattern = "DROP DATABASE test;";
    asprintf(&sql_query, sql_pattern);
    query_db(sql_query, 2);
    mx_strdel(&sql_query);
}*/
