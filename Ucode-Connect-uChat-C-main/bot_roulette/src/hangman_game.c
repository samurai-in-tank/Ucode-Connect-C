#include "cheers.h"

char *word = NULL;
char *hint = NULL;
char *hang_elements = "O|\\//\\";

typedef struct player_s {
    char        *name;
    char        *hang;
    char        *guessed_symbols;
    int         count_guessed_symbols;
    int         score;
    int         life;
    bool        is_dead;
} player_t;

char *get_underscore(int length) {
    char *arr = (char *)malloc(length);
    memset(arr, ' ', length);
    return arr;
}

/*void print_hang(char *hang) {
    printf("\n!HELP THE MAN HE IS DYING!");
    printf("\n\t||===== ");
    printf("\n\t||    | ");
    printf("\n\t||   %c%c%c", hang[2], hang[0], hang[3]);
    printf("\n\t||    %c", hang[1]);
    printf("\n\t||   %c %c", hang[4], hang[5]);
    printf("\n\t||      ");
}*/

void print_players(vector_t *vector_players) {
    for (vector_t *vector_player = vector_players; vector_player; vector_player = vector_player->next) {
        player_t *player = (player_t *)vector_player->data;
        printf("\n%s is %s\n", player->name, player->is_dead ? "dead" : "alive");
        printf("\nscore : %d\n",player->life);
    }
}

static bool check_player(vector_t *users_in_game, char *new_user) {
    if (users_in_game) {
        for (; users_in_game; users_in_game = users_in_game->next) {
            player_t *player = (player_t *)users_in_game->data;
            if (!strcmp(player->name, new_user)) {
                return false;
            }
        }
    }
    return true;
}

static void init_player(app_t *app, message_t *message) {
    player_t *player = (player_t *)malloc(sizeof(player_t));
    player->name = strdup(message->username);
    player->guessed_symbols = NULL;
    player->count_guessed_symbols = 0;
    player->score = 0;
    player->life = 6;
    player->is_dead = false;
    vector_push_back(&app->users_in_game, player);
    char message_to_server[60] = "Players play to game | ";
    strcat(message_to_server, (char *)player->name);
    send_message(app, 1, message_to_server, "");
    app->type=CREATE_MESSAGE_RESPONSE;
    receive_response(app);
}

void print_start_menu(app_t *app) {

     //vector_push_back(&app->users_in_game, player);
    char message_to_server[1024] = "               WELCOME_TO_HANGMANGAME        \
                                 ,     -You will get 5 chances to guess the right\
    word-       So help the Man and get...set...GO..!!        -\
                                 -Enter to play turn                    -\
                -If you are redy to go HIT (ENTER)                     ";
    //strcat(message_to_server, (char *)player->name);
    send_message(app, 1, message_to_server, "");
    app->type=CREATE_MESSAGE_RESPONSE;
    receive_response(app);

    //printf("----------------WELCOME_TO_HANGMANGAME---------------------");
    //printf("-------You will get 5 chances to guess the right word------");
    //printf("-------\n\n->So help the Man and get...set...GO..!!--------");
    //printf("--------------------Enter to play turn---------------------");
	//printf("--------------If you are redy to go HIT (ENTER)------------");
	//getchar();
    
    //print_hang(hang);
    //printf("\n\nThe word has %d alphabets\n\n", length);
}

void new_word_from_json(vector_t *vector_players) {
    json_value *j_value = open_json();
    int array_length = j_value->u.array.length;

    srand(time(NULL));
    int position = rand() % array_length;

    word = strdup(j_value->u.array.values[position]->u.object.values[0].value->u.string.ptr);
    hint = strdup(j_value->u.array.values[position]->u.object.values[1].value->u.string.ptr);

    for (vector_t *vector_player = vector_players; vector_player; vector_player = vector_player->next) {
        player_t *player = (player_t *)vector_player->data;
        player->guessed_symbols = get_underscore(strlen(word));
        player->count_guessed_symbols = 0;    
    }

    json_value_free(j_value);
    write(1, mx_itoa(vector_size(&vector_players)), strlen(mx_itoa(vector_size(&vector_players))));
}

void start_game(vector_t *vector_players, app_t *app) {
    //write(1, mx_itoa(vector_size(&vector_players)), strlen(mx_itoa(vector_size(&vector_players))));
    new_word_from_json(vector_players);
    //write(1, "1", 1);
    int position = 0;
    int length_word = strlen(word);
    
    //print_start_menu(app_t *app,"      ", length_word);
    printf("%s", get_underscore(length_word));
     //write(1, "2", 1);
      //write(1, mx_itoa(vector_size(&vector_players)), strlen(mx_itoa(vector_size(&vector_players))));

    while (vector_players && vector_players->next) {
        write(1, "1", 1);
        for (vector_t *vector_player = vector_players; vector_player;) {
            write(1, "2", 1);
            player_t *player = (player_t *)vector_player->data;
            write(1, "3", 1);
            bool is_guess = false;
            char user_input = '`';

            char *message_to_server = "Enter any word from a to z : ";
            send_message(app, 1, message_to_server, player->name);
            app->type = CREATE_MESSAGE_RESPONSE;
            receive_response(app);
            while (user_input == '`') {
                sleep(1 );
                vector_t *user = app->messages->tail;
                char *str = (char *)user->data;
                write(1, "4", 1);
                user_input = mx_tolower(str[0]);
                write(1, "5", 1);
            }

            for (int i = 0; i < length_word; i++) {
                if (user_input == word[i]) {
                    player->score++;
                    player->guessed_symbols[i] = user_input;
                    is_guess = true;
                }
            }
            write(1, "6", 1);
            if (player->count_guessed_symbols == length_word) {
                char str[50] = "Guess - ";
                strcat(str, player->name);

                send_message(app, 1, player->name, "");
                app->type = CREATE_MESSAGE_RESPONSE;
                receive_response(app);

                new_word_from_json(vector_players);
            }
            write(1, "7", 1);
            if (!is_guess) {
                write(1, "8", 1);
                player->life--;
                vector_player = vector_player->next;
                write(1, "a", 1);
                //print_hang(player->hang);
                write(1, "b", 1);
            }
            //write(1, "5", 1);
            if (player->life == 0) {
                write(1, "c", 1);
                write(1, mx_itoa(vector_player->id),strlen(mx_itoa(vector_player->id)));
                vector_delete(&vector_players, vector_player->id);
            }
            if (vector_size(&vector_players) == 1) {
                char str[50] = "Winner - ";
                strcat(str, player->name);

                send_message(app, 1, player->name, "");
                app->type = CREATE_MESSAGE_RESPONSE;
                receive_response(app);

                break;
            }
        }
        if (vector_size(&vector_players) == 1) {
            break;
        }
        print_players(vector_players);
        write(1, "d", 1);
    }
}

void hangman_game(app_t *app) {
    if (!app->messages) {
        return;
    }

    for (vector_t *node = app->messages; node; node = node->next) {
        message_t *message = (message_t *)node->data;
        if (strcmp("yes", message->text) == 0 && check_player(app->users_in_game, message->username)) {
            print_start_menu(app);
            printf("%s: %s\n", message->username, message->text);
            init_player(app, message);
        }
    }
    write(1, "1", 1);
    start_game(app->users_in_game,app);

    vector_free(&app->users_in_game);
}
