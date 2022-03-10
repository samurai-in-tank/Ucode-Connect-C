#include "cheers.h"

void loop(app_t *app, char **argv) {
    read_l(app);

    while (1) {
        if (app->type == CREATE_MESSAGE_QUERY) {
            char *buff = get_str("message");
            send_message(app, 1, buff, "");
            app->type = 3;
        }
        else if (app->type == UPDATE_QUERY) {
            send_update(app);
            app->type = 4;
        }
        else if (app->type == LOGOUT_QUERY) {
            send_logout(app);
            break;
        }
        else {

            vector_free(&app->messages);
            receive_response(app);

        
            
           //hangman_game(app);

            read_l(app);
        }
    }
}


/*
    for (int i = 0; i < 30; i++) {
        vector_free(&app->messages);
        send_update(app);
        app->type = 4;
        receive_response(app);

        for (vector_t *node = app->messages; node != NULL; node = node->next) {
            message_t *message = (message_t *)node->data;
            printf("%s: %s\n", message->username, message->text);
        }

        sleep(1);
    }
*/
