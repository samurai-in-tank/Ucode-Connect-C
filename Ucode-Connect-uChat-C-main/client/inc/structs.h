// structs.h
#ifndef CHEERS_STRUCTS_H
#define CHEERS_STRUCTS_H

#include "cheers.h"
#include "json.h"

typedef struct app_s {
	vector_t 		*users;
	vector_t		*chats;
	vector_t  		*messages;
    vector_t  		*all_messages;
	char			*token;
	char			*username;
	int 			user_icon;
	int				chat_id;
	int 			sockfd;
	int 			type;

    char *server_name;
    int server_online;

    GtkWidget *login_window;
    GtkWidget *main_window;

    GtkWidget *login_errors_label;
    GtkWidget *username_entry;
    GtkWidget *address_entry;
    GtkWidget *port_entry;
    GtkWidget *password_entry;

    GtkWidget *chat_name_label;
    GtkWidget *new_message_input;
    GtkWidget *messages_container;
    GtkWidget *chat_scroller;
    GtkWidget *messages_viewport;
    GtkWidget *chats_list;
    GtkWidget *greeting_message_title;
    GtkWidget *greeting_message_desc;
    GtkWidget *usericon_image;
    GtkWidget *username_label;
    GtkWidget *server_name_label;
    GtkWidget *server_online_label;
    GtkWidget *tabs_stack;

    GtkWidget *chat_box;
    GtkWidget *chatinfo_box;

    GtkWidget *chatinfo_icon;
    GtkWidget *chatinfo_title;
    GtkWidget *chatinfo_status;
    GtkWidget *chatinfo_desc;

    GtkWidget *games_list;
    GtkWidget *stickers_list;

    bool is_sending;
    bool is_updating;

    int argc;
    char **argv;
} app_t;

typedef struct message_s {
    int         id;
    int         type;
    int         chat_id;
    char        *username;
    int         user_icon;
    char        *text;
    bool        is_only_for_me;
    long        datetime;
} message_t;

typedef struct user_s {
    int         id;
    char        *username;
    char        *password;
    bool        online;
    int         current_chat_online;
} user_t;

typedef struct chat_s {
    int         id;
    char        *name;
    char        *status;
    char        *description;
    int         chat_icon;
} chat_t;

typedef struct game_s {
    int         id;
    char        *name;
} game_t;

#endif
