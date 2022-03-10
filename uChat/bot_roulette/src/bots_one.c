#include "cheers.h"

int index_user = 0;
int A = 7;
int B = 3;
int i = 7;

static void init_Players(app_t *app, message_t *message) {
    game_message_t *game_message = (game_message_t *)malloc(sizeof(game_message_t));
    char *message_text = NULL;

    game_message->user_name_bot_s = message->username;
    game_message->text_bot_s = message->text;
    game_message->isDead = false;
    vector_push_back(&app->users_in_game, game_message);

    asprintf(&message_text, "%s joined the game", message->username);

    app->type=2;
    sleep(2);
    send_message(app, 1, message_text, "");
    receive_response(app);
}

int Fibonachi(vector_t *base_nums) {
    int a = atoi((char *)vector_get(&base_nums, i - A)->data);
    int b = atoi((char *)vector_get(&base_nums, i - B)->data);
    return a >= b ? a - b : a - b + 10;
}

static void playTurn(game_message_t *user, vector_t *base_nums, int random1, int random2) {
    int shoot = Fibonachi(base_nums);
    printf("%d\n",shoot);
    vector_push_back(&base_nums, (void *)itoa(shoot));
    user->isDead = shoot == random1 || shoot == random2 ? true : false;
    i++;
}

static bool check_player(vector_t *users_in_game, char *new_user) {
    if (users_in_game) {
        for (; users_in_game; users_in_game = users_in_game->next) {
            game_message_t *game_message = (game_message_t *)users_in_game->data;
            if (!strcmp(game_message->user_name_bot_s, new_user)) {
                return false;
            }
        }
    }
    return true;
}

void bots_game(app_t *app) {
    bool in_cycle = true;

    while (in_cycle) {
        vector_free(&app->messages);
        send_update(app);
        app->type = 4;
        receive_response(app);

        for (vector_t *node = app->messages; node; node = node->next) {
            message_t *message = (message_t *)node->data;

            if (strcmp("/start_game bot_roulette", message->text) == 0) {
                in_cycle = false;
                break;
            }
        }

        sleep(2);
    }

    send_message(app, 1, "Russian roulette game was started! Write *yes* to join the game", "");
    app->type=CREATE_MESSAGE_RESPONSE;
    receive_response(app);

    sleep(10);

    send_update(app);
    app->type = 4;
    receive_response(app);

    for (vector_t *node = app->messages; node; node = node->next) {
        message_t *message = (message_t *)node->data;
        if (strcmp("yes", message->text) == 0 && check_player(app->users_in_game, message->username)) {
            printf("%s: %s\n", message->username, message->text);
            init_Players(app, message);
        }
    }
    
    vector_free(&app->messages);

    vector_t *base_nums = NULL;
    vector_push_back(&base_nums, (void *)itoa(3));
    vector_push_back(&base_nums, (void *)itoa(1));
    vector_push_back(&base_nums, (void *)itoa(5));
    vector_push_back(&base_nums, (void *)itoa(8));
    vector_push_back(&base_nums, (void *)itoa(2));
    vector_push_back(&base_nums, (void *)itoa(5));
    vector_push_back(&base_nums, (void *)itoa(0));

    srand(time(NULL));
    int random1 = rand() % 10;
    int random2 = atoi(vector_get(&base_nums, rand() & 7)->data); 

    vector_t *current_user = app->users_in_game;
    while (current_user && current_user->next) {
        
        for (vector_t *user = current_user; user; user = user->next){
            game_message_t *new_play = (game_message_t *)user->data;
            char *message_text = NULL;

            playTurn(new_play, base_nums, random1, random2);
           
            if (new_play->isDead) {
                asprintf(&message_text, "%s shoot and kill themself!", new_play->user_name_bot_s);

                app->type=2;
                send_message(app, 3, "sticker_dead", "");
                receive_response(app);
                vector_delete(&current_user, index_user);

                app->type=2;
                send_message(app, 1, message_text, "");
                receive_response(app);
                vector_delete(&current_user, index_user);

                sleep(2);
                break;
            }
            else {
                asprintf(&message_text, "%s shoot and just hear *click*!", new_play->user_name_bot_s);

                app->type=2;
                sleep(2);
                send_message(app, 1, message_text, "");
                receive_response(app);
                
                sleep(2);            
            }

            index_user++;
        }
        index_user = 0;
    }

    app->type=2;
    send_message(app, 1, "Player stay alive and win this game!", "");
    receive_response(app);
    vector_delete(&current_user, index_user);
}
