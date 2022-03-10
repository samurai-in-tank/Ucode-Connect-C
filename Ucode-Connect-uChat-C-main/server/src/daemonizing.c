#include "server.h"

void daemonizing() {
    pid_t pid = fork();

    if (pid < 0) {
        exit(1);
    }
    if (pid > 0) {
        exit(0);
    }
    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }

    signal(SIGHUP, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);

    pid = fork();

    if (pid < 0) {
        exit(1);
    }
    if (pid > 0) {
        exit(0);
    }

    umask(0);

    for (int i = 0; i < sysconf(_SC_OPEN_MAX); ++i) {
        close(i);
    }   
}
