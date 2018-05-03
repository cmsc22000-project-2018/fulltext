#ifndef INCLUDE_INPUT_H_
#define INCLUDE_INPUT_H_

/* Input struct */
typedef struct {
    char** commands;
} input;

/* Parses input commands */
void parse_input(char** commands);

#endif /* INCLUDE_INPUT_H_ */
