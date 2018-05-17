#ifndef _FULLTEXT_INPUT_H
#define _FULLTEXT_INPUT_H

/* Input struct */
typedef struct {
    char** commands;
} input;

/* Parses input commands */
void parse_input(char** commands);

#endif /* INCLUDE_INPUT_H_ */
