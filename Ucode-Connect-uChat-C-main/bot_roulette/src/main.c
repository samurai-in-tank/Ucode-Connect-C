// main.c

#include "cheers.h"

int main(int argc, char *argv[]) {
	if (argc != 3) {
        printf("\n Usage: %s <ip of server> <port>\n", argv[0]);
        return 1;
    }

	app_t *app = app_init();


    int sockfd = 0;
    struct sockaddr_in serv_addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        printf("\n inet_pton error occured\n");
        return 1;
    }

    printf("Connecting to the server...\n");
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Error : Connect Failed \n");
        printf("Retrying... \n\n");
        close(sockfd);
        return 1;
    }

    app->chat_id = 0;
    app->sockfd = sockfd;
    app->token = NULL;
    app->username = NULL;
    app->users_in_game = NULL;
    app->messages = NULL;

    char *password = "1";
    send_login(app, "gamebot", password);
    app->type = 5;
    receive_response(app);

    bots_game(app);

	//loop(app, argv);
	
	app_quit(app);

    close(sockfd);

	return 0;
}
