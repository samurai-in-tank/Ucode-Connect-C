// factory.c

#include "cheers.h"

GtkWidget* show_login_window(void) {
    GtkWidget *window;
    GtkBuilder *builder;
    GError* error = NULL;
    double from_bottom = 0;
    pthread_t tid;

    builder = gtk_builder_new ();
    if (!gtk_builder_add_from_file (builder, "resource/forms/login.ui", &error)) {
        g_critical ("Couldn't load file: %s", error->message);
        g_error_free (error);
    }

    gtk_builder_connect_signals (builder, NULL);

    window = GTK_WIDGET (gtk_builder_get_object (builder, "loginWindow"));
    if (!window) {
        g_critical ("Window widget error");
    }
    gtk_widget_set_name(GTK_WIDGET(window), "login_window");

    GtkCssProvider *cssProvider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(cssProvider, "resource/style/login.css", NULL);
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    app->login_errors_label = GTK_WIDGET(gtk_builder_get_object(builder, "login_errors_label"));
    app->username_entry = GTK_WIDGET(gtk_builder_get_object(builder, "username_entry"));
    app->address_entry = GTK_WIDGET(gtk_builder_get_object(builder, "address_entry"));
    app->port_entry = GTK_WIDGET(gtk_builder_get_object(builder, "port_entry"));
    app->password_entry = GTK_WIDGET(gtk_builder_get_object(builder, "password_entry"));

    g_object_unref (builder);

    if(app->argc >= 5) {
        gtk_entry_set_text(GTK_ENTRY(app->username_entry), app->argv[3]);
        gtk_entry_set_text(GTK_ENTRY(app->address_entry), app->argv[1]);
        gtk_entry_set_text(GTK_ENTRY(app->port_entry), app->argv[2]);
        gtk_entry_set_text(GTK_ENTRY(app->password_entry), app->argv[4]);
    }

    gtk_widget_show (window);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    return window;
}

GtkWidget* load_main_window(void) {
    GtkWidget *window, *button;
    GtkBuilder *builder;
    GError* error = NULL;
    double from_bottom = 0;

    builder = gtk_builder_new ();
    if (!gtk_builder_add_from_file (builder, "resource/forms/window.ui", &error)) {
        g_critical ("Couldn't load file: %s", error->message);
        g_error_free (error);
    }

    gtk_builder_connect_signals (builder, NULL);

    window = GTK_WIDGET (gtk_builder_get_object (builder, "mainWindow"));
    if (!window) {
        g_critical ("Window widget error");
    }
    gtk_widget_set_name(GTK_WIDGET(window), "main_window");

    // Chats Sidebar
    GtkWidget *chats_sidebar = GTK_WIDGET(gtk_builder_get_object(builder, "chats_sidebar"));
    gtk_widget_set_name(GTK_WIDGET(chats_sidebar), "chats_sidebar");

    GtkWidget *user_info = GTK_WIDGET(gtk_builder_get_object(builder, "user_info"));
    gtk_widget_set_name(GTK_WIDGET(user_info), "user_info");

    GtkWidget *chats_scroller = GTK_WIDGET(gtk_builder_get_object(builder, "chats_scroller"));
    gtk_widget_set_name(GTK_WIDGET(chats_scroller), "chats_scroller");

    app->chats_list = GTK_WIDGET(gtk_builder_get_object(builder, "chats_list"));
    gtk_widget_set_name(GTK_WIDGET(app->chats_list), "chats_list");

    GtkWidget *server_info = GTK_WIDGET(gtk_builder_get_object(builder, "server_info"));
    gtk_widget_set_name(GTK_WIDGET(server_info), "server_info");

    // Chat Box
    app->chat_box = GTK_WIDGET(gtk_builder_get_object(builder, "chat_box"));
    gtk_widget_set_name(GTK_WIDGET(app->chat_box), "chat_box");

    GtkWidget *chat_info = GTK_WIDGET(gtk_builder_get_object(builder, "chat_info"));
    gtk_widget_set_name(GTK_WIDGET(chat_info), "chat_info");

    app->chat_scroller = GTK_WIDGET(gtk_builder_get_object(builder, "chat_scroller"));
    gtk_widget_set_name(GTK_WIDGET(app->chat_scroller), "chat_scroller");

    GtkWidget *message_entry = GTK_WIDGET(gtk_builder_get_object(builder, "message_entry"));
    gtk_widget_set_name(GTK_WIDGET(message_entry), "message_entry");

    GtkWidget *tabs_sidebar = GTK_WIDGET(gtk_builder_get_object(builder, "tabs_sidebar"));
    gtk_widget_set_name(GTK_WIDGET(tabs_sidebar), "tabs_sidebar");

    GtkWidget *tabs_switch = GTK_WIDGET(gtk_builder_get_object(builder, "tabs_switch"));
    gtk_widget_set_name(GTK_WIDGET(tabs_switch), "tabs_switch");

    app->tabs_stack = GTK_WIDGET(gtk_builder_get_object(builder, "tabs_stack"));
    gtk_widget_set_name(GTK_WIDGET(app->tabs_stack), "tabs_stack");

    GtkWidget *games_scroller = GTK_WIDGET(gtk_builder_get_object(builder, "games_scroller"));
    gtk_widget_set_name(GTK_WIDGET(games_scroller), "games_scroller");

    app->games_list = GTK_WIDGET(gtk_builder_get_object(builder, "games_list"));
    gtk_widget_set_name(GTK_WIDGET(app->games_list), "games_list");

    GtkWidget *stickers_scroller = GTK_WIDGET(gtk_builder_get_object(builder, "stickers_scroller"));
    gtk_widget_set_name(GTK_WIDGET(stickers_scroller), "stickers_scroller");

    app->stickers_list = GTK_WIDGET(gtk_builder_get_object(builder, "stickers_list"));
    gtk_widget_set_name(GTK_WIDGET(app->stickers_list), "stickers_list");

    GtkWidget *greeting_message = GTK_WIDGET(gtk_builder_get_object(builder, "greeting_message"));
    gtk_widget_set_name(GTK_WIDGET(greeting_message), "greeting_message");

    app->chatinfo_box = GTK_WIDGET(gtk_builder_get_object(builder, "chatinfo_box"));
    gtk_widget_set_name(GTK_WIDGET(app->chatinfo_box), "chatinfo_box");

    GtkWidget *chatinfo_scroller = GTK_WIDGET(gtk_builder_get_object(builder, "chatinfo_scroller"));
    gtk_widget_set_name(GTK_WIDGET(chatinfo_scroller), "chatinfo_scroller");

    GtkWidget *chatinfo_bar = GTK_WIDGET(gtk_builder_get_object(builder, "chatinfo_bar"));
    gtk_widget_set_name(GTK_WIDGET(chatinfo_bar), "chatinfo_bar");

    GtkWidget *bot_beergame = GTK_WIDGET(gtk_builder_get_object(builder, "bot_beergame"));
    gtk_widget_set_name(GTK_WIDGET(bot_beergame), "bot_beergame");
    GtkWidget *bot_hangman = GTK_WIDGET(gtk_builder_get_object(builder, "bot_hangman"));
    gtk_widget_set_name(GTK_WIDGET(bot_hangman), "bot_hangman");
    GtkWidget *bot_roulette = GTK_WIDGET(gtk_builder_get_object(builder, "bot_roulette"));
    gtk_widget_set_name(GTK_WIDGET(bot_roulette), "bot_roulette");

    GtkWidget *chatinfo_container = GTK_WIDGET(gtk_builder_get_object(builder, "chatinfo_container"));
    gtk_widget_set_name(GTK_WIDGET(chatinfo_container), "chatinfo_container");
    app->chatinfo_icon = GTK_WIDGET(gtk_builder_get_object(builder, "chatinfo_icon"));
    gtk_widget_set_name(GTK_WIDGET(app->chatinfo_icon), "chatinfo_icon");
    app->chatinfo_title = GTK_WIDGET(gtk_builder_get_object(builder, "chatinfo_title"));
    gtk_widget_set_name(GTK_WIDGET(app->chatinfo_title), "chatinfo_title");
    app->chatinfo_status = GTK_WIDGET(gtk_builder_get_object(builder, "chatinfo_status"));
    gtk_widget_set_name(GTK_WIDGET(app->chatinfo_status), "chatinfo_status");
    app->chatinfo_desc = GTK_WIDGET(gtk_builder_get_object(builder, "chatinfo_desc"));
    gtk_widget_set_name(GTK_WIDGET(app->chatinfo_desc), "chatinfo_desc");

    app->chat_name_label = GTK_WIDGET(gtk_builder_get_object(builder, "chat_name_label"));
    app->new_message_input = GTK_WIDGET(gtk_builder_get_object(builder, "new_message_input"));
    app->messages_container = GTK_WIDGET(gtk_builder_get_object(builder, "messages_container"));
    gtk_widget_set_name(GTK_WIDGET(app->messages_container), "messages_container");
    app->messages_viewport = GTK_WIDGET(gtk_builder_get_object(builder, "messages_viewport"));
    app->greeting_message_title = GTK_WIDGET(gtk_builder_get_object(builder, "greeting_message_title"));
    app->usericon_image = GTK_WIDGET(gtk_builder_get_object(builder, "user_icon"));
    app->username_label = GTK_WIDGET(gtk_builder_get_object(builder, "username_label"));
    app->server_name_label = GTK_WIDGET(gtk_builder_get_object(builder, "server_name_label"));
    app->server_online_label = GTK_WIDGET(gtk_builder_get_object(builder, "server_online_label"));

    GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment (GTK_SCROLLED_WINDOW (app->chat_scroller));
    g_signal_connect (app->chat_scroller, "size-allocate", (GCallback) call_scroll_bottom_gravity, &from_bottom);
    g_signal_connect (adjustment, "value-changed", (GCallback) call_scroll_value_changed, &from_bottom);
    g_signal_connect(window, "destroy", G_CALLBACK(call_exit), NULL);
    g_signal_connect(window, "key_press_event", G_CALLBACK (call_enter_keypress), NULL);
    g_signal_connect(G_OBJECT(app->chats_list), "row-selected", G_CALLBACK(call_change_chat), "1");
    g_signal_connect(G_OBJECT(app->stickers_list), "child-activated", G_CALLBACK(call_send_sticker), "1");
    g_signal_connect(G_OBJECT(app->games_list), "row-selected", G_CALLBACK(call_play_game), "1");

	GtkCssProvider *cssProvider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(cssProvider, "resource/style/main.css", NULL);
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
    
    g_object_unref (builder);

    return window;
}

void show_main_window(GtkWidget *window) {
    pthread_t tid;
    gtk_widget_show (window);
    
    for (vector_t *node = app->chats; node != NULL; node = node->next) {
        chat_t *chat = (chat_t *)node->data;
        printf("%s\n", chat->name);
        create_chat(*chat);
    }

    GtkListBoxRow *row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(app->chats_list), 0);
    gtk_list_box_select_row(GTK_LIST_BOX(app->chats_list), row);

    set_user(app->username, app->user_icon);

    gtk_label_set_text(GTK_LABEL(app->server_name_label), app->server_name);
    set_online(vector_size(&app->users));

    char *path = NULL;

    for (int i = 1; i <= 32; i++) {
        asprintf(&path, "cartoon_pack/sticker_%d", i);
        create_sticker(path);
    }

    pthread_create(&tid, NULL, th_update, NULL);
}

void create_message(message_t mes) {
    GtkWidget *message, *icon, *username, *text, *datetime, *sticker;
    GtkBuilder *builder = gtk_builder_new ();
    GError* error = NULL;
    char *window_path = NULL, *icon_path = NULL;
    char *timestr = NULL;
    char *title = NULL;

    if(strcmp(app->username, mes.username) == 0) {
        if(mes.type == 3) window_path = "resource/forms/message_sticker_me.ui";
        else window_path = "resource/forms/message_text_me.ui";
    }
    else {
        if(mes.type == 3) window_path =  "resource/forms/message_sticker_other.ui";
        else window_path = "resource/forms/message_text_other.ui";

        if(mes.is_only_for_me) asprintf(&title, "direct from: %s", mes.username);
        else asprintf(&title, "%s", mes.username);
    }

    asprintf(&icon_path, "resource/img/user_icon/user_icon_%d.png", mes.user_icon);

    if (!gtk_builder_add_from_file (builder, window_path, &error)) {
        g_critical ("Couldn't load file: %s", window_path);
    }
    message = GTK_WIDGET (gtk_builder_get_object (builder, "message"));
    if (!message) {
        g_critical ("Window widget error");
    }

    if(mes.type == 3) {
        char *sticker_path = NULL;

        asprintf(&sticker_path, "resource/img/stickers/%s.png", mes.text);

        icon = GTK_WIDGET(gtk_builder_get_object(builder, "message_icon"));
        sticker = GTK_WIDGET(gtk_builder_get_object(builder, "message_sticker"));

        gtk_image_set_from_file(GTK_IMAGE(icon), icon_path);
        gtk_image_set_from_file(GTK_IMAGE(sticker), sticker_path);
    }
    else {
        icon = GTK_WIDGET(gtk_builder_get_object(builder, "message_icon"));
        username = GTK_WIDGET(gtk_builder_get_object(builder, "message_username"));
        text = GTK_WIDGET(gtk_builder_get_object(builder, "message_text"));
        datetime = GTK_WIDGET(gtk_builder_get_object(builder, "message_datetime"));

        timestr = ctime(&mes.datetime);
        timestr[strlen(timestr) - 1] = '\0';

        if(username != NULL) gtk_label_set_text(GTK_LABEL(username), title);
        gtk_label_set_text(GTK_LABEL(text), mes.text);
        gtk_label_set_text(GTK_LABEL(datetime), timestr);
        gtk_image_set_from_file(GTK_IMAGE(icon), icon_path);
    }

    gtk_box_pack_start(GTK_BOX(app->messages_container), message, false, true, 0);
    g_object_unref (builder);
}

void create_chat(chat_t c) {
    GtkWidget *chat, *icon, *title, *status;
    GtkBuilder *builder = gtk_builder_new ();
    GError* error = NULL;
    char *icon_path = NULL;

    asprintf(&icon_path, "resource/img/chat_icon/chat_icon_%d.png", c.chat_icon);

    if (!gtk_builder_add_from_file (builder, "resource/forms/chat.ui", &error)) {
        g_critical ("Couldn't load file: message_other.ui");
    }

    chat = GTK_WIDGET (gtk_builder_get_object (builder, "chat"));
    if (!chat) {
        g_critical ("Window widget error");
    }

    icon = GTK_WIDGET(gtk_builder_get_object(builder, "chat_icon"));
    title = GTK_WIDGET(gtk_builder_get_object(builder, "chat_title"));
    status = GTK_WIDGET(gtk_builder_get_object(builder, "chat_status"));

    gtk_image_set_from_file(GTK_IMAGE(icon), icon_path);
    gtk_label_set_text(GTK_LABEL(title), c.name);
    gtk_label_set_text(GTK_LABEL(status), c.status);

    gtk_widget_set_name(chat, itoa(c.chat_icon));

    gtk_list_box_insert(GTK_LIST_BOX(app->chats_list), chat, -1);
        
    g_object_unref(builder);
}

void create_sticker(const char *sticker_path) {
    GtkWidget *sticker, *icon;
    GtkBuilder *builder = gtk_builder_new ();
    GError* error = NULL;
    char *path = NULL;

    asprintf(&path, "resource/img/stickers/%s.png", sticker_path);

    if (!gtk_builder_add_from_file (builder, "resource/forms/sticker.ui", &error)) {
        g_critical ("Couldn't load file: message_other.ui");
    }

    sticker = GTK_WIDGET (gtk_builder_get_object (builder, "sticker"));
    if (!sticker) {
        g_critical ("Window widget error");
    }

    icon = GTK_WIDGET(gtk_builder_get_object(builder, "sticker_icon"));

    gtk_image_set_from_file(GTK_IMAGE(icon), path);

    gtk_widget_set_name(sticker, sticker_path);

    gtk_flow_box_insert(GTK_FLOW_BOX(app->stickers_list), sticker, -1);
        
    g_object_unref(builder);
}

void change_chat(int chat_id) {
    char *title = NULL, *text = NULL;
    char *icon_path = NULL;
    chat_t *chat = (chat_t *)vector_get(&app->chats, chat_id)->data;

    asprintf(&title, "Welcome to %s!", chat->name);
    asprintf(&icon_path, "resource/img/chat_icon/chat_icon_%d.png", chat->chat_icon);

    gtk_label_set_text(GTK_LABEL(app->greeting_message_title), title);
    gtk_label_set_text(GTK_LABEL(app->chat_name_label), chat->name);

    gtk_image_set_from_file(GTK_IMAGE(app->chatinfo_icon), icon_path);
    gtk_label_set_text(GTK_LABEL(app->chatinfo_title), chat->name);
    gtk_label_set_text(GTK_LABEL(app->chatinfo_status), chat->status);
    gtk_label_set_text(GTK_LABEL(app->chatinfo_desc), chat->description);
}

void reshow_old_messages(int chat_id) {
    gtk_container_foreach(GTK_CONTAINER(app->messages_container), call_delete_message, NULL);

    for (vector_t *node = app->all_messages; node != NULL; node = node->next) {
        message_t *message = (message_t *)node->data;

        if(message->chat_id == chat_id) {
            printf("%s: %s\n", message->username, message->text);
            create_message(*message);
        }
    }
}

void set_user(char *username, int user_icon) {
    char *icon_path = NULL;

    asprintf(&icon_path, "resource/img/user_icon/user_icon_%d.png", user_icon);

    gtk_label_set_text(GTK_LABEL(app->username_label), username);
    gtk_image_set_from_file(GTK_IMAGE(app->usericon_image), icon_path);
}

void set_online(int online) {
    char *str = NULL;

    asprintf(&str, "%d online", online);

    gtk_label_set_text(GTK_LABEL(app->server_online_label), str);
}

void show_login_error(bool is_shown, const char *text) {
    if(!is_shown) {
        gtk_widget_hide(app->login_errors_label);
        return;
    }

    gtk_widget_show(app->login_errors_label);
    gtk_label_set_text(GTK_LABEL(app->login_errors_label), text);
}