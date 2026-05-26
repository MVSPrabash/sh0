
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "exec.h"

void execute_command(char** argv) {
    if (argv[0] == NULL) {
        return;
    }

    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {  // Child Proc
        execvp(argv[0], argv);
        perror("execvp failed");
        exit(1);
    }

    int childStatus;
    waitpid(pid, &childStatus, 0);
        
    if (WIFEXITED(childStatus)) {
        printf("Exit Status: %d\n", WEXITSTATUS(childStatus));
    }

}

