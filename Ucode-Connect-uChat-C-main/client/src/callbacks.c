// callbacks.c

#include "cheers.h"

void call_scroll_value_changed (GtkAdjustment *adjustment, gpointer user_data) {
    double *from_bottom = user_data;

    double value = gtk_adjustment_get_value(adjustment);
    double upper = gtk_adjustment_get_upper(adjustment);
    double page_size = gtk_adjustment_get_page_size(adjustment);

    *from_bottom = upper - page_size - value;
}

void call_scroll_bottom_gravity (GtkWidget *scrolled_window, GdkRectangle *allocation, gpointer user_data) {
    GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW (scrolled_window));

    double *from_bottom = user_data;

    double upper = gtk_adjustment_get_upper(adjustment);
    double page_size = gtk_adjustment_get_page_size(adjustment);

    gtk_adjustment_set_value(adjustment, upper - page_size - *from_bottom);
}

void call_change_chat(GtkListBox* self, GtkListBoxRow* row, gpointer data) {
    const char *name = gtk_widget_get_name(GTK_WIDGET(row));
    app->chat_id = atoi(name);
    change_chat(app->chat_id);
    reshow_old_messages(app->chat_id);
    g_print("Chat changed: %d\n", app->chat_id);
    call_show_chat();
}

void *th_send_game(void *args) {
    while(app->is_updating);
    app->is_sending = true;
    char *command = NULL;

    if(strlen((char *)args) < 1) {
        pthread_exit(NULL);
        return NULL;
    }

    asprintf(&command, "/start_game %s", (char *)args);

    send_message(app, 1, command, "");

    app->type = 3;
    receive_response(app);

    app->is_sending = false;

    gtk_list_box_unselect_all(GTK_LIST_BOX(app->games_list));
    pthread_exit(NULL);
    return NULL;
}

void call_play_game(GtkListBox* self, GtkListBoxRow* row, gpointer data) {
    if(row == NULL) return;
    pthread_t tid;
    const char *name = gtk_widget_get_name(GTK_WIDGET(row));

    pthread_create(&tid, NULL, th_send_game, (void *)name);
}

void *th_send_sticker(void *args) {
    while(app->is_updating);
    app->is_sending = true;

    if(strlen((char *)args) < 1) {
        pthread_exit(NULL);
        return NULL;
    }

    send_message(app, 3, (char *)args, "");

    app->type = 3;
    receive_response(app);

    app->is_sending = false;

    gtk_flow_box_unselect_all(GTK_FLOW_BOX(app->stickers_list));
    pthread_exit(NULL);
    return NULL;
}

void call_send_sticker(GtkFlowBox* self, GtkFlowBoxChild* child, gpointer data) {
    pthread_t tid;
    const char *sticker = strdup(gtk_widget_get_name(GTK_WIDGET(child)));
    pthread_create(&tid, NULL, th_send_sticker, (void *)sticker);
}

void call_delete_message(GtkWidget* widget, gpointer data) {
    gtk_container_remove (GTK_CONTAINER(app->messages_container), widget);
}

gboolean call_enter_keypress(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (event->keyval == GDK_KEY_Return) {
        call_send_message();
        return TRUE;
    }
    return FALSE;
}

void *th_send_message(void *args) {
    while(app->is_updating);
    app->is_sending = true;
    write(1, "sender:\n", 7);

    if(strlen((char *)args) < 1) {
        pthread_exit(NULL);
        return NULL;
    }

    send_message(app, 1, (char *)args, "");

    app->type = 3;
    receive_response(app);

    write(1, "sd\n", 3);
    app->is_sending = false;
    pthread_exit(NULL);
    return NULL;
}

void call_send_message(void) {
    pthread_t tid;
    const char *message = mx_strtrim(gtk_entry_get_text(GTK_ENTRY(app->new_message_input)));
    pthread_create(&tid, NULL, th_send_message, (void *)message);

    gtk_entry_set_text(GTK_ENTRY(app->new_message_input), "");
}

void call_exit(void) {
    send_logout(app);
    gtk_main_quit();
}

void call_login_submit(void) {
    int error = 0;
    const char *username = gtk_entry_get_text(GTK_ENTRY(app->username_entry));
    const char *address = gtk_entry_get_text(GTK_ENTRY(app->address_entry));
    const char *port = gtk_entry_get_text(GTK_ENTRY(app->port_entry));
    const char *password = gtk_entry_get_text(GTK_ENTRY(app->password_entry));

    show_login_error(false, NULL);

    app->sockfd = app_connect(address, port);

    if(app->sockfd < 0) {
        show_login_error(true, "Server error: Connect Failed");
        return;
    }

    send_login(app, username, password);
    app->type = 5;
    error = receive_response(app);

    switch (error) {
        case 0:
            gtk_widget_hide(app->login_window);
            show_main_window(app->main_window);
            break;
        
        case 1:
            show_login_error(true, "Login error: Too small username");
            break;

        case 2:
            show_login_error(true, "Login error: Too long username");
            break;

        case 3:
            show_login_error(true, "Login error: Incorrect symbols in username");
            break;

        case 4:
            show_login_error(true, "Login error: Username is already exis");
            break;

        case 5:
            show_login_error(true, "Login error: Incorrect password");
            break;
        
        default:
            break;
    }
}

void call_set_stack_games(void) {
    gtk_stack_set_visible_child_name(GTK_STACK(app->tabs_stack), "games");
}

void call_set_stack_stickers(void) {
    gtk_stack_set_visible_child_name(GTK_STACK(app->tabs_stack), "stickers");
}

void call_show_chatinfo(void) {
    gtk_widget_hide(app->chat_box);
    gtk_widget_show(app->chatinfo_box);
}

void call_show_chat(void) {
    gtk_widget_hide(app->chatinfo_box);
    gtk_widget_show(app->chat_box);
}