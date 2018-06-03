#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include <ctype.h>
#include <simclist.h>
#include "search.h"
#include "match.h"
#include "trie.h"

int find_match(char* line, trie_t* words,
               int pos_start, int lineNum, list_t* matches)
{
	char* dup = strdup(line);
	char* line2 = strdup(line);
	int pos = pos_start;
	char* token = strtok(line2, " ,.!?\r\t\n");
	match* foundMatch = NULL;

	while (token != NULL) {
		for(int i = 0; token[i]; i++){
  			token[i] = tolower(token[i]);
		}
		
		if (trie_contains(words, token) == 0) {
		// if (strncasecmp(token, word, wordlen) == 0) {
			
			/* Config match */
			foundMatch = match_new(token, lineNum, pos, dup);
			match_append(foundMatch, matches);

			/* Clean-up */
			free(dup);

			/* Return */
			return pos;
		}

		pos += strlen(token) + 1;
		token = strtok(NULL, " ,.!?\r\t\n");

	}

	return -1;

}

list_t* parse_file_buffered(FILE* pf, int start_line,
                            int end_line, trie_t* words, list_t* matches)
{
	char* line = NULL;
	int BUFFER_LENGTH = 100;
	size_t len = 0;
	ssize_t read;

	int found = -1;
	int lineNum = start_line;

	printf("\n ... searching through lines %d - %d ... \n", start_line, end_line);

	while (lineNum <= end_line &&
	        (read = getline(&line, &len, pf)) != -1) {

		// Filter text lines
		char sanitized[strlen(line) + 1];
		strncpy(sanitized, line, strlen(line));
		sanitized[strcspn(sanitized, "\r\n")] = 0;
		char* dupLine = strdup(sanitized);

		char line2[strlen(sanitized) + 1];
		strncpy(line2, sanitized, strlen(sanitized));
		found = find_match(sanitized, words, 1, lineNum, matches);
		
		// Multiple occurences in a sentence
		while (found != -1) {
			match* foundMatch = match_get_at_index(list_size(matches) - 1,
				                                       matches);

			int wordlen = strlen(match_get_word(foundMatch));

			if (found + wordlen < read) {
				memset(sanitized, ' ', found + wordlen);

				found = find_match(sanitized, words, found + wordlen + 2,
				                   lineNum, matches);

				if (strcmp(sanitized, dupLine) != 0) {
					foundMatch = match_get_at_index(list_size(matches) - 1,
					                                       matches);

					match_set_line(foundMatch, dupLine);
				}
			}
		}

		lineNum++;
		free(dupLine);
	}
	//if no matches found and is not EOF, look through next 100 lines.
	if (list_size(matches) == 0 && !feof(pf))
	{
		parse_file_buffered(pf, end_line + 1, end_line + BUFFER_LENGTH, words, matches);
	}
	//if EOF, notify user
	if (feof(pf))
	{
		printf("\n ... reached EOF ... \n");
	}

	return matches;
}

void display_prev_match(list_t* matches, int index) {

	if (index == 0) {
		printf("\n...wrap-around to last match found...\n\n");
	}

	match_display(match_prev(index, matches));

}

void display_next_match(list_t* matches, int index) {

	if (index == list_size(matches) - 1) {
		printf("\n...wrap-around to first match found...\n\n");

		// parse more
		// if EOF has been reached (how do we know that?),
		//  we say ...wrap-around to first match found...
		// else
		//  display next match

	}

	match_display(match_next(index, matches));

}
