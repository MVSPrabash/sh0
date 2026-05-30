#include "background.h"

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

int background_pos(char** argv) {
    int bg_pos = -1;
    int i = 0;
    for (; argv[i] != NULL; i++) {
        if (strcmp(argv[i], "&") == 0) {
            if (bg_pos != -1) return -2;
            
            bg_pos = i;
        }
    }
    
    if (bg_pos == 0 || (bg_pos != i - 1 && bg_pos != -1)) return -2;
    
    if (bg_pos != -1) argv[bg_pos] = NULL;

    return bg_pos;
}

void reap_background_processes() {
    int status;
    pid_t terminated_pid = waitpid(-1, &status, WNOHANG);

    if (terminated_pid == 0) return ;

    while (terminated_pid != -1) {
        printf("[%d] Exited\n", terminated_pid);
        terminated_pid = waitpid(-1, &status, WNOHANG);
    }
}