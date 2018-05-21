#ifndef _FULLTEXT_SEARCH_H_
#define _FULLTEXT_SEARCH_H_

/** 
  @brief Reads from a text file, append to the previous
  @      match list of the search term but does not return list
  @      MINIMAL IMPLEMENTATION : SINGLE SEARCH TERM
  @param fp: pointer to the file to perform search on
  @param match: the existing match_list or NULL of the search term
  @param search_word: the search term of type string
  @return 0 upon reaching EOF, 1 if match is found
*/
int minimal_read_until_next_match(FILE *fp, list_t *matches, char *search_word);

/** 
  @brief Reads from a text file, append to the previous
  @      particulat match list of the search term from the matches_set
  @      but does not return the updated set
  @      MINIMAL IMPLEMENTATION : SET_SIZE == 1
  @param fp: pointer to the file to perform search on
  @param matches_set: an array of existing match_list or NULL of the search term
  @param word_set: an array of the search terms
  @param SET_SIZE: number of search terms in word_set
  @param line_num: the previous line of occurrence
  @return this particular new match node
*/
int single_word_read_until_next_match(FILE *fp, list_t **matches_set, 
	char **word_set, int SET_SIZE, int line_num);


/** 
  @brief Reads from a text file, append to the previous
  @      particulat match list of the search term from the matches_set
  @      but does not return the updated set
  @param fp: pointer to the file to perform search on
  @param matches_set: an array of existing match_list or NULL of the search term
  @param word_set: an array of the search terms
  @param SET_SIZE: number of search terms in word_set
  @param line_num: the previous line of occurrence
  @return this particular new match node
*/
int read_until_next_match(FILE *fp, list_t **matches_set,
 char **word_set, int SET_SIZE, int line_num);

#endif /* _FULLTEXT_SEARCH_H_ */
