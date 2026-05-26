#include "builtins.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int execute_builtin(char** argv) {          // builtin dispatcher
    if (strcmp(argv[0], "exit") == 0) {
        printf("BYE\n");
        exit(0);
    }
    else if (strcmp(argv[0], "pwd") == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("pwd");
            return 1;
        }
        printf("%s\n", cwd);
        return 1;
    }
    else if (strcmp(argv[0], "cd") == 0) {
        if (argv[1] == NULL) {
            char* home = getenv("HOME");
            if (home == NULL) {
                printf("cd: HOME not set\n");
                return 1;
            }
            if (chdir(home) != 0) {
                perror("cd");
            };
        }
        else if (chdir(argv[1]) == 0) {
            // success
        }
        else {
            perror("cd");
        }
        return 1;
    } else if (strcmp(argv[0], "help") == 0) {
        printf("sh0 builtins:\n");
        printf("  cd     Change directory\n");
        printf("  pwd    Print current working directory\n");
        printf("  exit   Exit the shell\n");
        printf("  help   Show this help message\n");

        return 1;
    }
    return 0;
}