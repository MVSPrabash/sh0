#ifndef EXEC_H
#define EXEC_H

void execute_command(char** argv);

void execute_external(char** argv, int background);

int background_pos(char** argv);

#endif