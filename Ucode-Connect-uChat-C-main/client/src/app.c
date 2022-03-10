// init.c

#include "cheers.h"

app_t *app_init(int argc, char **argv) {
	app_t *app = NULL;
 

	// allocate memory for app struct
	app = (app_t *) malloc(sizeof(app_t));
	if (app == NULL) return NULL;
	memset(app, 0, sizeof(app_t));

    app->chat_id = 0;
    app->sockfd = 0;
    app->token = NULL;
    app->username = NULL;
    app->is_sending = false;
    app->is_updating = false;
    app->argc = argc;
    app->argv = argv;
	
	return app;
}

void app_quit(app_t *app) {
	free(app);
}

int app_connect(const char *address, const char *port) {
    int sockfd = 0;
    struct sockaddr_in serv_addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error : Could not create socket \n");
        exit(1);
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(port));

    if (inet_pton(AF_INET, address, &serv_addr.sin_addr) <= 0) {
        printf("\n inet_pton error occured\n");
        return -1;
    }

    printf("Connecting to the server...\n");
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Error : Connect Failed \n");
        close(sockfd);
        return -1;
    }

    return sockfd;
}
