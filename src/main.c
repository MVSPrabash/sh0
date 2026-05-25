/**
 * Author: MVS Prabash
 * Description: Main entry point for the sh0 shell implementation.
 */

// C std libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// linux/unix libs
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "parser.h"

#define CMD_BUFF_SIZE 1024

int main() {
    char cmd[CMD_BUFF_SIZE];

    while (1) {
        printf("sh0# ");
        if (fgets(cmd, CMD_BUFF_SIZE, stdin) == NULL) {
            printf("BYE\n");
            break;
        }

        cmd[strcspn(cmd, "\n")] = '\0';

        if (strcmp(cmd, "exit") == 0) {
            printf("BYE\n");
            break;
        }

        char** argv = tokenize(cmd);

        if (argv[0] == NULL) {
            free(argv);
            continue;
        }

        pid_t pid = fork();
        
        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        }
        else if (pid == 0) {  // Child Proc
            printf("Child proc running\n");
            execvp(argv[0], argv);
            perror("execvp failed");
            exit(1);
        }

        int childStatus;
        waitpid(pid, &childStatus, 0);
        
        if (WIFEXITED(childStatus)) {
            printf("Exit Status: %d\n", WEXITSTATUS(childStatus));
        }

        free(argv);  // dealloc
    }
}