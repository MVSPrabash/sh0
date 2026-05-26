#include "exec.h"
#include "builtins.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


void execute_command(char** argv) {
    if (argv[0] == NULL) {
        return;
    }

    if (!execute_builtin(argv)) {
        execute_external(argv);
    }
}

void execute_external(char** argv) {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        execvp(argv[0], argv);
        perror("execvp failed");
        exit(1);
    }

    int childStatus;
    waitpid(pid, &childStatus, 0);
        
    if (WIFEXITED(childStatus)) {
        printf("[exit %d]\n", WEXITSTATUS(childStatus));
    }
}
