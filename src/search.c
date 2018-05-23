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

int find_match(char* line, char* word, int pos_start)
{
    printf("looking at line: %s len %d and word %s len %d\n\n", line, strlen(line), word, strlen(word));
    if (strlen(word) > strlen(line)) return -1;
    char line2[strlen(line)+1];
    strcpy(line2, line);
    int pos = pos_start;
    char* token = strtok(line2, " ");
    while (token != NULL) {

        if (strcmp(token, word) == 0) {
	        printf("\nline: %s\n", line);
            printf("match found: %s at pos %d\n", token, pos);
            return pos;
        }
        pos += strlen(token) + 1;
        token = strtok(NULL, " ");
    }
    return -1;
}

// // see search.h
// int minimal_read_until_next_match(FILE *fp, list_t *matches, 
// 	char *search_word, int line_num)
// {	
// 	char *line = NULL;
// 	size_t len = 0;
// 	ssize_t read = 0;
// 	char *token, *saveptr, *saveln;
// 	int pos = 0;

// 	// the search_word has no previous matches
// 	if (matches == NULL) {
// 		list_init(matches);
// 	}

// 	while ((read = getline(&line, &len, fp)) != -1) {
// 		pos = 0;
// 		// makes a copy of line so that moving fp will not affect string
// 		saveln = strdup(line);
// 		token = strtok_r(line, " ,.!?\t\n", &saveptr);
// 		while (token != NULL) {
// 			pos++;			

// 			// inefficient search algorithm
// 			if (strncmp(search_word, token, strlen(search_word)) == 0) {
// 				// creates new match, append to list; prints node and returns
// 				match *match_node = new_match(search_word, line_num, pos);
// 				append_(match_node, matches);
// 				return 1;
// 			}
// 			// advance to next word in line
// 			token = strtok_r(NULL, " ,.!?\t\n", &saveptr);
// 		}
// 		free(saveln);
// 	}
// 	return 0;
// }

// // see search.h
// int single_word_read_until_next_match(FILE *fp, list_t **matches_set, 
// 	char **word_set, int SET_SIZE, int line_num)
// {
// 	SET_SIZE = 1;
// 	assert(matches_set != NULL);
// 	assert(word_set != NULL);

// 	list_t matches = *matches_set[0];
// 	char *search_word = word_set[0];
// 	assert(search_word != NULL);

// 	int ret = minimal_read_until_next_match(fp, matches, search_word, line_num);
// 	return ret;
// }

// // see search.h
// int read_until_next_match(FILE *fp, list_t **matches_set,
//  char **word_set, int SET_SIZE, int line_num)
//  {
//  	char *line = NULL;
// 	size_t len = 0;
// 	ssize_t read = 0;
// 	char *token, *saveptr, *saveln;
// 	int pos = 0;

// 	for (int i = 0; i < SET_SIZE; i++) {
// 		char *search_word = word_set[i];
// 		list_t matches = *matches_set[i];

// 		if (matches == NULL) {
// 			list_init(matches);
// 		}
// 		// start reading line by line
// 		while ((read = getline(&line, &len, fp)) != -1) {
// 			pos = 0;
// 			saveln = strdup(line);
// 			token = strtok_r(line, " ,.!?\t\n", &saveptr);
// 			while (token != NULL) {
// 				pos++;

// 				// inefficient search algorithm
// 				if (strncmp(search_word, token, strlen(search_word)) == 0) {
// 					match *match_node = new_match(search_word, line_num, pos);
// 					append_(match_node, matches);
// 					return 1;
// 				}
// 				token = strtok_r(NULL, " ,.!?\t\n", &saveptr);token = strtok_r(NULL, " ,.!?\t\n", &saveptr);
// 			}
// 			free(saveln);
// 		}
// 		return 0;
// 	}
// }