#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

char** push_token(char** argv, int* argc, int* capacity, char* token) {
    if (*argc >= *capacity - 1) {
        *capacity *= 2;

        char** temp = realloc(argv, sizeof(char*) * (*capacity));

        if (temp == NULL) {
            perror("realloc");
            free(argv);
            exit(1);
        }

        argv = temp;
    }

    argv[(*argc)++] = token;
    return argv;
}

char* make_token(const char* start, int len) {
    char* token = malloc(len + 1);

    if (token == NULL) {
        perror("malloc");
        exit(1);
    }

    memcpy(token, start, len);
    token[len] = '\0';

    return token;
}

typedef enum {
    DEFAULT,
    IN_WORD
} State;

char** tokenize(char* cmd) {
    int capacity = 10;
    int argc = 0;

    char** argv = malloc(sizeof(char*) * capacity);

    State state = DEFAULT;

    char* word_start = NULL;

    for (char* ch = cmd; ; ch++) {
        if (state == DEFAULT) {
            if (*ch == '\0')
                break;

            if (*ch == ' ' || *ch == '\t')
                continue;

            if (*ch == '<' || *ch == '|' || *ch == '&') {
                char* token = make_token(ch, 1);
                argv = push_token(argv,
                                  &argc,
                                  &capacity,
                                  token);

                continue;
            }

            if (*ch == '>') {
                if (*(ch + 1) == '>') {
                    argv = push_token(
                        argv,
                        &argc,
                        &capacity,
                        make_token(ch, 2)
                    );

                    ch++;
                }
                else {
                    argv = push_token(
                        argv,
                        &argc,
                        &capacity,
                        make_token(ch, 1)
                    );
                }

                continue;
            }

            word_start = ch;
            state = IN_WORD;
        }

        if (state == IN_WORD) {
            int delimiter =
                *ch == '\0' ||
                *ch == ' ' ||
                *ch == '\t' ||
                *ch == '<' ||
                *ch == '>' ||
                *ch == '|' ||
                *ch == '&';

            if (delimiter) {
                argv = push_token(
                    argv,
                    &argc,
                    &capacity,
                    make_token(word_start,
                               ch - word_start)
                );

                state = DEFAULT;

                if (*ch == '\0')
                    break;

                ch--;      // reprocess delimiter
            }
        }
    }

    argv[argc] = NULL;
    return argv;
}

void free_tokens(char** argv) {
    if (argv == NULL)
        return;

    for (int i = 0; argv[i] != NULL; i++) {
        free(argv[i]);
    }

    free(argv);
}


// Old one
char** tokenize_old(char* cmd) {
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
