#ifndef _FULLTEXT_SEARCH_H_
#define _FULLTEXT_SEARCH_H_

/** 
  @brief Reads from a text file, append to the previous
  @      match list of the search term
  @      MINIMAL IMPLEMENTATION : SINGLE SEARCH TERM
  @param match: the existing match_list or NULL of the search term
  @param search_word: the search term of type string
  @param fp: pointer to the file to perform search on
  @return this particular new match node
*/
list_t *minimal_read_until_next_match(list_t *match_list, char *search_word,
	FILE *fp);

#endif /* _FULLTEXT_SEARCH_H_ */
