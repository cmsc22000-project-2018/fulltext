#ifndef _FULLTEXT_MATCH_H_
#define _FULLTEXT_MATCH_H_

/* Match struct */
typedef struct {
    char* word;
    int line;
} match;

/**
	@brief Creates new match.
	@param word: the match string. 
  @param line: the line the match is on
	@return a pointer to the match.
*/
match* new_match(char* word, int line);

/** 
  @brief Initializes the match.
  @param match: pointer to match. 
  @param word: the match string. 
  @param line: the line the match is on
  @return 0 for success
*/
int init_match(match* match, char* word, int line);

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
  @brief Goes to next item in linked list 
  @param match: pointer to match
  @param matches: doubly linked list (dll) of matches
  @return pointer to next match
*/
match* next_match(match* match, GList* matches);

/** 
 @brief Goes to previous item in linked list 
 @param match* match: pointer to match
 @param matches: dll of matches
 @return pointer to previous match
*/
match* prev_match(match* match, GList* matches);

/** 
  @brief Inserts at specific index in match struct 
  @param newMatch: pointer to new match struct
  @param index: index to insert the match into dll
  @param matches: dll of matches
  @return pointer of GList representing list of all matches
 */
GList* insert_at(match* newMatch, int index, GList* matches);

/** 
  @brief Inserts at end of match struct 
  @param newMatch: pointer to new match struct
  @param matches: dll of matches
  @return pointer of GList representing list of all matches
*/
GList* append_(match* newMatch, GList* matches);

/** 
  @brief Removes at specific index in match struct 
  @param index: index of match to remove
  @param matches: dll of matches
  @return pointer of GList representing list of all matches
*/
GList* remove_at(int index, GList* matches);

/** 
  @brief Returns the match at the given index 
  @param index: index of desired match
  @param matches: dll of matches
  @return pointer of match at the index
*/
match* get_at_index(int index, GList* matches);

/** 
  @brief Gets the index of current match 
  @param match: match struct at unknown index
  @param matches: dll of matches
  @return int index of match
*/
int get_index(match* match, GList* matches);

#endif /* _FULLTEXT_MATCH_H_ */