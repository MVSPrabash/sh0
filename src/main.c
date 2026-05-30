/**
 * Author: MVS Prabash
 * Description: Main entry point for the sh0 shell implementation.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "exec.h"
#include "background.h"

#define CMD_BUFF_SIZE 1024

int main() {
    char cmd[CMD_BUFF_SIZE];

    while (1) {
        reap_background_processes();

        printf("sh0# ");
        fflush(stdout);

        if (fgets(cmd, CMD_BUFF_SIZE, stdin) == NULL) {
            printf("\nBYE\n");
            break;
        }

        cmd[strcspn(cmd, "\n")] = '\0';

        char** argv = tokenize(cmd);

        execute_command(argv);

        free(argv);  // dealloc
    }
}