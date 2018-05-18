#ifndef _FULLTEXT_PARSER_H_
#define _FULLTEXT_PARSER_H_

// next_token, read_string, init_parser borrowed
// from CS152 Win 18, project blockchain

/* @struct stringArray struct
   @contains a string array as well as an int for length
*/
typedef struct stringArray {
	char **array;
	int len;
} stringArray;


/**
    @brief Read the next non-empty char.
    @param fp: pointer to the file to be read
    @return Nothing.
 */
void next_token(FILE *fp);

/**
    @brief Read the current string into a string pointer
    @if NULL, returns 0
    @param s: pointer to string just read in
    @return an int indicating success or failure.
 */
int read_string(char** s);

/**
    @brief Initialize parser, skip any leading blank lines
    @param fp: pointer to the file to be read
    @return Nothing.
 */
void init_parser(FILE *fp);

/**
    @brief Parse file into a string array
    @param fp: pointer to the file to be read
    @return a pointer to the struct StringArray.
 */
stringArray *parse_to_arr(FILE *fp);

#endif /* INCLUDE_FULLTEXT_PARSER_H_ */
