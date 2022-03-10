#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <time.h>
#include <sys/signal.h>
#include <strings.h>
#include "vector.h"
#include "libmx.h"
#include "json.h"
#include "libjson.h"

typedef enum request_e {
	CREATE_MESSAGE_QUERY,
    UPDATE_QUERY,
    LOGIN_QUERY,
    CREATE_MESSAGE_RESPONSE,
    UPDATE_RESPONSE,
    LOGIN_RESPONSE,
    LOGOUT_QUERY
} request_t;

typedef struct server_s {
    char        *server_name;
    char        *server_password;
    vector_t    *chats_vector;
    char        *first_user_username;
    char        *first_user_text;
} server_t;

typedef struct message_s {
    int         id;
    int         type;
    int         chat_id;
    char        *username;
    int         user_icon;
    char        *text;
    char        *for_user;
    long        datetime;
} message_t;

typedef struct user_s {
    int         id;
    char        *token;
    char        *username;
    int         user_icon;
    int         current_chat_id;
} user_t;

typedef struct chat_s {
    int         id;
    char        *name;
    char        *status;
    char        *description;
    //int         active_game;
    int         chat_icon;
    //vector_t    *users_id;
} chat_t;

typedef struct game_s {
    int         id;
    char        *name;
} game_t;

typedef struct app_s {
    char    *token;
    char    *current_username;
    char    *server_password;
    int     type;
    int     last_message_id;
    int     user_icon;
    int     current_chat;
    bool    logout;
} app_t;

void daemonizing();
void *query_db(char *query, int type);
/*bool check_user(int user_id, int chat_id);
bool is_user(char *username);*/
void insert_user(char *token, char *username, int user_icon, int chat_id);
/*int insert_chat(char *title, char *subscribe, int active_game, int type, int user_id);*/
void insert_message(int type, int chat_id, char *username, int user_icon, char *text, char *for_user, long int datetime);
//void insert_chat_reletion(int user_id, int chat_id, bool is_admin);
message_t *get_message(int message_id);
user_t *get_user_by_id(int user_id);
vector_t *get_usernames(void);
/*user_t *get_user_by_username_and_password(char *username, char *password);
chat_t *get_chat(int chat_id);*/
int get_last_message_id();
//int get_next_message_id(int last_message_id);
int get_last_user_id(void);
/*int get_user_id(char *username);
int get_last_chat_id(void);
void remove_chat(int chat_id);*/
void remove_user(char *username);
//void remove_chat_reletion(int user_id, int chat_id);
void update_user_username(char *new_username, char *username);
void update_user_icon(int new_user_icon, char *username);
void update_user_chat(int chat_id, char *username);
/*void update_user_name(char *name, int user_id);
void update_user_password(char *password, int user_id);
void update_user_online(bool is_online, int user_id);
void update_message(char *text, int message_id);
void rename_group(char *title, int chat_id);*/
char *request_hundler(json_value *query, app_t *app, vector_t *chats_vector, char *server_name);

void get_messages(json_value *arr, int last_message_id, char *username);
void get_chats(json_value *arr, vector_t *chats_vector);
void get_users_online(json_value *arr);
