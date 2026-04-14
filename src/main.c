// C standard libraries
#include <stdio.h>
#include <string.h>

#define CMD_BUFF_SIZE 1024

int main() {
    char cmd[CMD_BUFF_SIZE];

    while (1) {
        printf("sh0# ");
        fgets(cmd, CMD_BUFF_SIZE, stdin);

        // Tokenization

        // Command execution
        if (strcmp(cmd, "exit\n") == 0) {
            printf("BYE\n");
            break;
        }
    }
}