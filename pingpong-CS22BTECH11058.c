#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int pipe_fds[2];
    char buffer[10];

    pipe(pipe_fds);

    int child_pid = fork();

    if (child_pid < 0) {
        printf("Error: Failed to create child process\n");
        exit(1);
    }
    else if (child_pid == 0) {
        read(pipe_fds[0], buffer, sizeof(buffer));
        printf("[%d - Child] Received message: %s\n", getpid(), buffer);
        write(pipe_fds[1], "pong", 5);
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        exit(0);
    }
    else {
        write(pipe_fds[1], "ping", 5);
        wait(0);
        read(pipe_fds[0], buffer, sizeof(buffer));
        printf("[%d - Parent] Received message: %s\n", getpid(), buffer);
        close(pipe_fds[0]);
        close(pipe_fds[1]);
    }

    exit(0);
}