// functions.h
#ifndef CHEERS_FUNCTIONS_H
#define CHEERS_FUNCTIONS_H

#include "cheers.h"
#include "json.h"
#include "libjson.h"

app_t *app_init(int argc, char **argv);
void app_quit(app_t *app);
void *th_update(void *data);
void connect_styles(void);
int app_connect(const char *address, const char *port);

// Server communication functions
void send_login(app_t *app, const char *username, const char *server_password);
void send_message(app_t *app, int type, const char *text, char *for_user);
void send_update(app_t *app);
void send_logout(app_t *app);
void send_query(json_value *arr, int sockfd);
int receive_response(app_t *app);


json_value *get_response(int sockfd);
void get_messages(app_t *app, json_value *response, int num_array);
void get_chats(app_t *app, json_value *response, int num_array);
void get_user_online(app_t *app, json_value *response, int num_array);

// factory
GtkWidget* show_login_window(void);
GtkWidget* load_main_window(void);
void show_main_window(GtkWidget *window);
void create_message(message_t mes);
void create_chat(chat_t c);
void create_sticker(const char *sticker_path);
void change_chat(int chat_id);
void reshow_old_messages(int chat_id);
void set_user(char *username, int user_icon);
void set_online(int online);
void show_login_error(bool is_shown, const char *text);

// callbacks
void call_scroll_value_changed(GtkAdjustment *adjustment, gpointer user_data);
void call_scroll_bottom_gravity(GtkWidget *scrolled_window, GdkRectangle *allocation, gpointer user_data);
void call_change_chat(GtkListBox* self, GtkListBoxRow* row, gpointer data);
void call_delete_message(GtkWidget* widget, gpointer data);
gboolean call_enter_keypress(GtkWidget *widget, GdkEventKey *event, gpointer data);
void call_send_message(void);
void call_exit(void);
void call_show_chatinfo(void);
void call_show_chat(void);
void call_send_sticker(GtkFlowBox* self, GtkFlowBoxChild* child, gpointer data);
void call_play_game(GtkListBox* self, GtkListBoxRow* row, gpointer data);

// utils
char *itoa(int num);
char *get_str(char *str);
void read_l(app_t *app);

#endif // !CHEERS_FUNCTIONS_H
