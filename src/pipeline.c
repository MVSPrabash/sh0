#include "pipeline.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int pipe_pos(char** argv) {
    int pos = -1;

    for (int i = 0; argv[i] != NULL; i++) {
        if (strcmp(argv[i], "|") == 0) {
            if (pos != -1) return -2;    // multiple pipes not supported
            pos = i;
        }
    }

    return pos;
}

void execute_pipe(char** argv, int p_pos) {
    argv[p_pos] = NULL;

    char** left = argv;
    char** right = &argv[p_pos + 1];

    if (*left == NULL || *right == NULL) {
        fprintf(stderr, "sh0: invalid pipe syntax\n");
        return ;
    }

    int pipefd[2];  // 0R 1W

    if(pipe(pipefd) == -1) {
        perror("pipe");
        return ;
    }

    pid_t left_pid = fork();

    if (left_pid < 0) {
        perror("fork");
        return ;
    }
    else if (left_pid == 0) {   // left child
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        close(pipefd[1]);
        if (execvp(left[0], left) == -1) {
            perror("execvp");
            exit(1);
        }
    }

    pid_t right_pid = fork();
    
    if (right_pid < 0) {
        perror("fork");
        return ;
    }
    else if (right_pid == 0) {  // right child
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        close(pipefd[0]);
        if (execvp(right[0], right) == -1) {
            perror("execvp");
            exit(1);
        }
    }


    // sh0 parent

    close(pipefd[0]);
    close(pipefd[1]);
    
    int left_status, right_status;

    waitpid(left_pid, &left_status, 0);
    waitpid(right_pid, &right_status, 0);
}