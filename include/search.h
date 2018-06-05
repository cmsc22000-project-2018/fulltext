#ifndef _FULLTEXT_SEARCH_H_
#define _FULLTEXT_SEARCH_H_

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include "match.h"
#include "../src/simclist.h"
#include "trie.h"

/**
  @brief Searches for a match in a line given a starting position
         and an end position
  @param line Line to search
  @param t Trie containing all search terms
  @param pos_start Character number in sentence to start search at
  @param line_num Line number to keep track of match's line number
  @param matches List of matches
  @param found_token A token that is found to match a word in trie
  #updated return
  @return list of matches
  ---
  @return position number of match if match found
  @return -1 if no match found
 */
int find_match_trie(char* line, trie_t *t, int pos_start,
        int line_num, list_t* matches, char *found_token);

/**
  @brief Searches a file from line x to line y looking for given trie
  @param pf Pointer to file
  @param start_line Start text line to search through
  @param end_line Last text line to search through (inclusive)
  @param t Trie containing all search terms
  @param matches List of matches
  @return list of matches
 */
list_t* parse_file_buffered_trie(FILE* pf, int start_line,
 int end_line, trie_t *t, list_t* matches);

/**
  @brief Searches for a match in a line given a starting position
         and an end position
  @param line Line to search
  @param word Word to search for
  @param pos_start Character number in sentence to start search at
  @param line_num Line number to keep track of match's line number
  @param matches List of matches
  #updated return
  @return list of matches
  ---
  @return position number of match if match found
  @return -1 if no match found
 */
int find_match(char* line, trie_t* words, int pos_start,
 int line_num, list_t* matches);

/**
  @brief Searches a file from line x to line y looking for given word
  @param pf Pointer to file
  @param section the pointer to the section# of the file that was last parsed, so the most recent value of the int will be available.
  @param word Words to search for
  @param matches List of matches
  @return list of matches
 */
list_t* parse_file_buffered(FILE* pf, int* section, trie_t* words, list_t* matches);

/**
  @brief Searches a file for matches present in a trie from batch file
  @param fp Pointer to file
  @param t Trie containing search terms
  @param matches List of matches
  @return list of matches
 */
list_t *find_matches_batch(FILE *fp, trie_t *t, list_t *matches);

/**
  @brief Displays matches present in a trie from batch file
  @param bp Stream of batch file
  @param matches List of matches
  @return None
 */
void display_matches_batch(FILE *bp, list_t *matches);

/**
  @brief Prints out the prev match from list to std out
  @param fileptr Pointer to file to be searched
  @param batchptr Pointer to batch file
  @param strarr Array of search words
  @return void
 */
void search_batch(FILE *fileptr, FILE *batchptr, trie_t *words_trie);

/**
  @brief Prints out the prev match from list to std out
  @param matches List of matches
  @param index Current match index
  @return void
 */
void display_prev_match(list_t* matches, int index);

/**
  @brief Prints out the next match from list to std out
  @param matches List of matches
  @param index Current match index
  @param pf Pointer to file
  @param words Words to search for
  @param section the pointer to the section# of file last parsed
  @return void
 */
void display_next_match(list_t* matches, int index, FILE* pf, trie_t* words, int* section);

#endif /* _FULLTEXT_SEARCH_H_ */
