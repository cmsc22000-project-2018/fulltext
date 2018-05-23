#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include "simclist.c"
#include "simclist.h"
#include "match.h"

// see search.h
int minimal_read_until_next_match(FILE *fp, list_t *matches, 
	char *search_word, int line_num)
{	
	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	char *token, *saveptr, *saveln;
	int pos = 0;

	// the search_word has no previous matches
	if (matches == NULL) {
		list_init(matches);
	}

	while ((read = getline(&line, &len, fp)) != -1) {
		pos = 0;
		// makes a copy of line so that moving fp will not affect string
		saveln = strdup(line);
		token = strtok_r(line, " ,.!?\t\n", &saveptr);
		while (token != NULL) {
			pos++;			

			// inefficient search algorithm
			if (strncmp(search_word, token, strlen(search_word)) == 0) {
				// creates new match, append to list; prints node and returns
				match *match_node = new_match(search_word, line_num, pos);
				append_(match_node, matches);
				return 1;
			}
			// advance to next word in line
			token = strtok_r(NULL, " ,.!?\t\n", &saveptr);
		}
		free(saveln);
	}
	return 0;
}

// see search.h
int single_word_read_until_next_match(FILE *fp, list_t **matches_set, 
	char **word_set, int SET_SIZE, int line_num)
{
	SET_SIZE = 1;
	assert(matches_set != NULL);
	assert(word_set != NULL);

	list_t matches = matches_set[0];
	char *search_word = word_set[0];
	assert(search_word != NULL);

	int ret = minimal_read_until_next_match(fp, matches, search_word, line_num);
	return ret;
}

// see search.h
int read_until_next_match(FILE *fp, list_t **matches_set,
 char **word_set, int SET_SIZE, int line_num)
 {
 	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	char *token, *saveptr, *saveln;
	int pos = 0;

	for (int i = 0; i < SET_SIZE; i++) {
		char *search_word = word_set[i];
		list_t matches = matches_set[i];

		if (matches == NULL) {
			list_init(matches);
		}
		// start reading line by line
		while ((read = getline(&line, &len, fp)) != -1) {
			pos = 0;
			saveln = strdup(line);
			token = strtok_r(line, " ,.!?\t\n", &saveptr);
			while (token != NULL) {
				pos++;

				// inefficient search algorithm
				if (strncmp(search_word, token, strlen(search_word)) == 0) {
					match *match_node = new_match(search_word, line_num, pos);
					append_(match_node, matches);
					return 1;
				}
				token = strtok_r(NULL, " ,.!?\t\n", &saveptr);
			}
			free(saveln);
		}
		return 0;
	}
