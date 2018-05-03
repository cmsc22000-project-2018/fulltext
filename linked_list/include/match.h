#ifndef INCLUDE_MATCH_H_
#define INCLUDE_MATCH_H_

/* Match struct */
typedef struct {
    char* word;
    int line;
    match* prev;
    match* next;
} match;

/* Create new match */
match* new_match(char* word, int line);

/* Initialize match */
void init_match(match* match, char* word, int line);

/* Free match */
int free_match(match* match);

/* Find word in match struct */
char* get_word(match* match);

/* Return the line number of match struct */
int get_line(match* match);

/* Go to next item in linked list */
match* next_match(match* match);

/* Go to previous item in linked list */
match* prev_match(match* match);

/* Insert at specific index in match struct */
void insert_at(match* match, match* new, int index);

/* Insert at end of match struct */
void append(match* match, match* new);

/* Remove at specific index in match struct */
void remove_at(match* match, int index);

/* Return the match at the given index */
match* get_at_index(match* match, int index);

/* Get the index of current match */
int get_index(match* match);

#endif /* INCLUDE_MATCH_H_ */