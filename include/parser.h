#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_

// next_token, read_string, init_parser borrowed
// from CS152 Win 18, project blockchain

/* stringArray struct */
typedef struct stringArray {
	char **array;
	int len;
} stringArray;

// read the next non-empty char
void next_token(FILE *fp);

// read the current string; if NULL, returns 0
int read_string(char** s);

// initialize parser, skip any leading blank lines
void init_parser(FILE *fp);

// parse txt into a string array
stringArray *parse_to_arr(FILE *fp);

#endif /* INCLUDE_PARSER_H_ */