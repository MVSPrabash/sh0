#ifndef PARSER_H
#define PARSER_H

char** tokenize(char* cmd);

void free_tokens(char** argv);

#endif
