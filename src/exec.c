#include "exec.h"
#include "builtins.h"
#include "pipeline.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>


void execute_command(char** argv) {
    if (argv[0] == NULL) return ;

    if (execute_builtin(argv)) return ;

    int p_pos = pipe_pos(argv);

    if (p_pos >= 0) {
        execute_pipe(argv, p_pos);
    } else if (p_pos == -1) {
        execute_external(argv);
    } else {
        fprintf(stderr, "sh0: multiple pipes not supported\n");
    }
}

void execute_external(char** argv) {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    else if (pid == 0) {
        char* outputFile = NULL;
        int outputFlags = 0;
        char* inputFile = NULL;

        for (int i = 0; argv[i] != NULL; i++) {
            if (strcmp(argv[i], ">") == 0) {
                if (argv[i + 1] == NULL) {
                    fprintf(stderr, "sh0: syntax error, expected a filename\n");
                    exit(1);
                }
                outputFile = argv[i + 1];
                outputFlags = O_WRONLY | O_TRUNC | O_CREAT;

                argv[i] = NULL;
            }
            else if (strcmp(argv[i], "<") == 0) {
                if (argv[i + 1] == NULL) {
                    fprintf(stderr, "sh0: syntax error, expected a filename\n");
                    exit(1);
                }
                inputFile = argv[i + 1];
                argv[i] = NULL;
            }
            else if (strcmp(argv[i], ">>") == 0) {
                if (argv[i + 1] == NULL) {
                    fprintf(stderr, "sh0: syntax error, expected a filename\n");
                    exit(1);
                }
                outputFile = argv[i + 1];
                outputFlags = O_WRONLY | O_CREAT | O_APPEND;

                argv[i] = NULL;
            }
        }

        if (outputFile != NULL) {
            int fd = open(outputFile, outputFlags, 0644);
            if (fd < 0) {
                perror("sh0");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        if (inputFile != NULL) {
            int fd = open(inputFile, O_RDONLY);
            if (fd < 0) {
                perror("sh0");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        execvp(argv[0], argv);
        perror("execvp");
        exit(1);
    }

    int childStatus;
    waitpid(pid, &childStatus, 0);
        
    if (WIFEXITED(childStatus)) {
        // printf("[exit %d]\n", WEXITSTATUS(childStatus));
    }
}
