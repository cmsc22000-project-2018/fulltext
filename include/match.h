#ifndef INCLUDE_MATCH_H_
#define INCLUDE_MATCH_H_

/* Match struct */
typedef struct {
    char* word;
    int line;
} match;

/* 
 * Creates new match 
 *
 * Params: 
 *  - char* word: the match string
 *  - int line: the line the match is on
 *
 * Returns:
 *  - a pointer to the match
 */
match* new_match(char* word, int line);

/* 
 * Initializes match 
 *
 * Params:
 *  - match* match: pointer to match
 *  - char* word: the match string
 *  - int line: the line the match is on
 *
 * Returns:
 *  - 0 for success
 */
int init_match(match* match, char* word, int line);

/* 
 * Frees match 
 *
 * Params:
 *  - match* match: pointer to match
 *
 * Returns:
 *  - -1 for failure, 0 for success
 */
int free_match(match* match);

/* 
 * Finds word in match struct 
 *
 * Params:
 *  - match* match: pointer to match
 *
 * Returns:
 *  - string in match struct
 */
char* get_word(match* match);

/* 
 * Returns the line number of match struct 
 *
 * Params:
 *  - match* match: pointer to match
 *
 * Returns:
 *  - int representing line number
 */
int get_line(match* match);

/* 
 * Goes to next item in linked list 
 *
 * Params:
 *  - match* match: pointer to match
 *  - GList* matches: doubly linked list (dll) of matches
 *
 * Returns:
 *  - pointer to next match
 */
match* next_match(match* match, GList* matches);

/* 
 * Goes to previous item in linked list 
 *
 * Params:
 *  - match* match: pointer to match
 *  - GList* matches: dll of matches
 *
 * Returns:
 *  - pointer to previous match
 */
match* prev_match(match* match, GList* matches);

/* 
 * Inserts at specific index in match struct 
 * 
 * Params:
 *  - match* newMatch: pointer to new match struct
 *  - int index: index to insert the match into dll
 *  - GList* matches: dll of matches
 *
 * Returns:
 *  - pointer of GList representing list of all matches
 */
GList* insert_at(match* newMatch, int index, GList* matches);

/* 
 * Inserts at end of match struct 
 *
 * Params:
 *  - match* newMatch: pointer to new match struct
 *  - GList* matches: dll of matches
 *
 * Returns:
 *  - pointer of GList representing list of all matches
 */
GList* append_(match* newMatch, GList* matches);

/* 
 * Removes at specific index in match struct 
 *
 * Params:
 *  - int index: index of match to remove
 *  - GList* matches: dll of matches
 *
 * Returns:
 *  - pointer of GList representing list of all matches
 */
GList* remove_at(int index, GList* matches);

/* 
 * Returns the match at the given index 
 * 
 * Params:
 *  - int index: index of desired match
 *  - GList* matches: dll of matches
 *
 * Returns:
 *  - pointer of match at the index
 */
match* get_at_index(int index, GList* matches);

/* 
 * Gets the index of current match 
 * 
 * Params:
 *  - match* match: match struct at unknown index
 *  - GList* matches: dll of matches
 *
 * Returns:
 *  - int index of match
 */
int get_index(match* match, GList* matches);

#endif /* INCLUDE_MATCH_H_ */