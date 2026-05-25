#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

char** tokenize(char* cmd) {
    int capacity = 10;

    int argc = 0;
    char** argv = ( char ** ) malloc(capacity * sizeof(char *));

    char* token = strtok(cmd, " \t");

    while (token != NULL) {
        argv[argc++] = token;
        token = strtok(NULL, " \t");

        if (argc >= capacity - 1) {
            capacity *= 2;
            argv = realloc(argv, capacity * sizeof(char *));
        }
    }
    argv[argc] = NULL;
    
    return argv;
}


