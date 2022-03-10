// functions.h
#ifndef CHEERS_FUNCTIONS_H
#define CHEERS_FUNCTIONS_H

#include "cheers.h"
#include "json.h"
#include "libjson.h"

app_t *app_init(void);
void app_quit(app_t *app);
void hangman_game(app_t *app);
void loop(app_t *app, char **argv);

// Server communication functions
void send_login(app_t *app, char *username, char *server_password);
void send_message(app_t *app, int type, const char *text, char *for_user);
void send_update(app_t *app);
void send_logout(app_t *app);
void send_query(json_value *arr, int sockfd);
void receive_response(app_t *app);


json_value *get_response(int sockfd);
void get_messages(app_t *app, json_value *response, int num_array);
void get_chats(app_t *app, json_value *response, int num_array);
void get_user_online(app_t *app, json_value *response, int num_array);

//utils
char *itoa(int num);
char *get_str(char *str);
void read_l(app_t *app);

//bot
void bots_game(app_t *app);

json_value *open_json();

#endif // !CHEERS_FUNCTIONS_H
