#ifndef _FULLTEXT_PARSER_H_
#define _FULLTEXT_PARSER_H_

// next_token, read_string, init_parser borrowed
// from CS152 Win 18, project blockchain

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
    @return a pointer to the array, setting last entry to NULL
 */
char **parse_to_arr(FILE *fp);

/**
    @brief Load array of strings into trie
    @param strarray: array of strings
    @return 0 if success, otherwise -1
*/
int trie_from_stringarray(char **strarray);

#endif /* INCLUDE_FULLTEXT_PARSER_H_ */
