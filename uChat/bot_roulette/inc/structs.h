// structs.h
#ifndef CHEERS_STRUCTS_H
#define CHEERS_STRUCTS_H

#include "cheers.h"
#include "json.h"

typedef struct app_s {
    vector_t        *users_in_game;
	vector_t 		*users;
	vector_t		*chats;
	vector_t  		*messages;
	char			*token;
	char			*username;
	int 			user_icon;
	int				chat_id;
	int 			sockfd;
	int 			type;
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


//bot
typedef struct game_message_s {
    char *user_name_bot_s;
    char *text_bot_s;
    bool isDead;
}game_message_t;

#endif
