// main.c

#include "cheers.h"

app_t *app;

void *th_update(void *data) {
    while(true) {
        while(app->is_sending);
        app->is_updating = true;
        write(1, "update:\n", 7);

        vector_free(&app->messages);

        send_update(app);
        app->type = 4;
        receive_response(app);

        for (vector_t *node = app->messages; node != NULL; node = node->next) {
            message_t *message = (message_t *)node->data;
            if(message->chat_id == app->chat_id) {
                //printf("%s: %s\n", message->username, message->text);
                create_message(*message);
            }
        }

        set_online(vector_size(&app->users));

        write(1, "ud\n", 3);
        app->is_updating = false;
        usleep(1000000);
    }

    return NULL;
}

int main(int argc, char **argv) {
	app = app_init(argc, argv);

    gtk_init (&argc, &argv);

    app->login_window = show_login_window();
    app->main_window = load_main_window();

    gtk_main ();
	
	app_quit(app);

	return 0;
}
