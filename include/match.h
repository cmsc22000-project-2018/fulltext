#ifndef _FULLTEXT_MATCH_H_
#define _FULLTEXT_MATCH_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include "simclist.h"

/* Match struct */
typedef struct {
    char* word;
    int lineNum;
    int position;
    char* line;
} match;

/**
  @brief Creates new match.
  @param word: the match string. 
  @param lineNum: the lineNum the match is on
  @param position: the position of the match
  @return a pointer to the match.
*/
match* new_match(char* word, int lineNum, int position, char* line);

/** 
  @brief Initializes the match.
  @param match: pointer to match. 
  @param word: the match string. 
  @param lineNum: the lineNum the match is on
  @param position: the position of the match
  @return 0 for success
*/
int init_match(match* match, char* word, int lineNum, int position, char* line);

/** 
  @brief Frees match 
  @param match: pointer to match
  @return -1 for failure
  @return 0 for success
*/
int free_match(match* match);

/** 
  @brief Finds word in match struct 
  @param match: pointer to match
  @return string in match struct
*/
char* get_word(match* match);

/** 
  @brief Returns the lineNum number of match struct 
  @param match: pointer to match
  @return int representing lineNum number
*/
int get_line_num(match* match);

/** 
  @brief Returns the position number of match struct 
  @param match: pointer to match
  @return int representing position
*/
int get_position(match* match);

/** 
  @brief Returns the string in which match was found
  @param match: pointer to match
  @return line string in match struct
*/
char* get_line(match* match);

/** 
  @brief Goes to next item in linked list 
  @param match: pointer to match
  @param matches: doubly linked list (dll) of matches
  @return pointer to next match, or NULL if not found
*/
match* next_match(match* match, list_t* matches);

/** 
 @brief Goes to previous item in linked list 
 @param match* match: pointer to match
 @param matches: dll of matches
 @return pointer to previous match, or NULL if not found
*/
match* prev_match(match* match, list_t* matches);

/** 
  @brief Inserts at specific index in match struct 
  @param newMatch: pointer to new match struct
  @param index: index to insert the match into dll
  @param matches: dll of matches
 */
void insert_at(match* newMatch, int index, list_t* matches);

/** 
  @brief Inserts at end of match struct 
  @param newMatch: pointer to new match struct
  @param matches: dll of matches
*/
void append_(match* newMatch, list_t* matches);

/** 
  @brief Removes at specific index in match struct 
  @param index: index of match to remove
  @param matches: dll of matches
*/
void remove_at(int index, list_t* matches);

/** 
  @brief Returns the match at the given index 
  @param index: index of desired match
  @param matches: dll of matches
  @return pointer of match at the index, or NULL if not found
*/
match* get_at_index(int index, list_t* matches);

/** 
  @brief Gets the index of current match 
  @param match: match struct at unknown index
  @param matches: dll of matches
  @return int index of match, or negative if not found
*/
int get_index(match* match, list_t* matches);

/** 
  @brief Displays information about list used for testing
  @param matches: dll of matches
  @return void
*/
void info_list(list_t* matches);

/** 
  @brief Displays the info of a match
  @param match: a match to print
  @return 1 success
  @return -1 failure
*/
int display_match(match* match);

#endif /* _FULLTEXT_MATCH_H_ */
