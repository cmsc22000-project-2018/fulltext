#ifndef _FULLTEXT_MATCH_H_
#define _FULLTEXT_MATCH_H_

/* Match struct */
/*typedef struct {
    char* word;
    int line;
    int position;
} match; */

/**
  @brief Creates new match.
  @param word: the match string. 
  @param line: the line the match is on
  @param position: the position of the match
  @return a pointer to the match.
*/
match* new_match(char* word, int line, int position);

/** 
  @brief Initializes the match.
  @param match: pointer to match. 
  @param word: the match string. 
  @param line: the line the match is on
  @param position: the position of the match
  @return 0 for success
*/
int init_match(match* match, char* word, int line, int position);

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
  @brief Returns the line number of match struct 
  @param match: pointer to match
  @return int representing line number
*/
int get_line(match* match);

/** 
  @brief Returns the position number of match struct 
  @param match: pointer to match
  @return int representing position
*/
int get_position(match* match);

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

#endif /* _FULLTEXT_MATCH_H_ */
