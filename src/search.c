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

int find_match_trie(char* line, trie_t *t, 
    int pos_start, int lineNum, list_t* matches, char *found_token)
{
	if (t == NULL) {
		perror("empty trie");
		return -1;
	}
    char* dup = strdup(line);
    char* line2 = strdup(line);
    int pos = pos_start;
    char* token = strtok(line2, " ,.!?\r\t\n");
    match* foundMatch = NULL;

    while (token != NULL) {

      if (trie_contains(t, token) == 0) {
        
            /* Config match */
            foundMatch = match_new(token, lineNum, pos, dup);
            match_append(foundMatch, matches);
            /* Save the token found */
            found_token = strdup(token);
            assert (found_token);
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

list_t* parse_file_buffered_trie(FILE* pf, int start_line, 
    int end_line, trie_t *t, list_t* matches)
{
	if (t == NULL) {
		perror("empty trie");
		return NULL;
	}
    char *line = NULL;
    char *found_token = NULL;
    int wordlen = 0;
    size_t len = 0;
    ssize_t read;

    int found = -1;
    int lineNum = start_line;

    while (lineNum <= end_line &&
     (read = getline(&line, &len, pf)) != -1) {
        char sanitized[strlen(line) + 1];
        strncpy(sanitized, line, strlen(line));
        sanitized[strcspn(sanitized, "\r\n")] = 0;
        char* dupLine = strdup(sanitized);

        char line2[strlen(sanitized) + 1];
        strncpy(line2, sanitized, strlen(sanitized));
        found = find_match_trie(sanitized, t, 1, lineNum, matches, found_token);

        if (found_token != NULL)
            wordlen = strlen(found_token);
        while (found != -1 && found + wordlen < read) {
            memset(sanitized, ' ', found + wordlen);
            found_token = NULL; // where to free found_token ?
            found = find_match_trie(sanitized, t, found + wordlen + 2,
             lineNum, matches, found_token);
            
            if (strncmp(sanitized, dupLine, strlen(sanitized)) != 0) {
                match* foundMatch = match_get_at_index(list_size(matches) - 1,
                 matches);

                match_set_line(foundMatch, dupLine);
            }

        }

        lineNum++;
        free(dupLine);
    }

    return matches;
}

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

list_t* parse_file_buffered(FILE* pf, int* section,
                            trie_t* words, list_t* matches)
{
    char* line = NULL;
    int BUFFER_LENGTH = 160;
    size_t len = 0;
    ssize_t read;

    (*section)++;
    int end_line = (*section) * BUFFER_LENGTH;
    int start_line = end_line - (BUFFER_LENGTH - 1);

    int found = -1;
    int lineNum = start_line;

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

                found = find_match(sanitized, words, found + wordlen + 1,
                                   lineNum, matches);

                if (strncmp(sanitized, dupLine, BUFFER_LENGTH) != 0) {

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
        parse_file_buffered(pf, section, words, matches);
    }
    // if EOF, notify user
    else if (feof(pf))
    {
        printf("\n...search completed...\n");
    }

    return matches;
}


list_t *find_matches_batch(FILE *fp, trie_t *t, list_t *matches)
{
	if (t == NULL) {
		perror("empty trie");
		return NULL;
	}
    char *line = NULL;
    char *found_token = NULL;
    int wordlen = 0;
    size_t len = 0;
    ssize_t read;

    int found = -1;
    int lineNum = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        char sanitized[strlen(line) + 1];
        strncpy(sanitized, line, strlen(line));
        sanitized[strcspn(sanitized, "\r\n")] = 0;
        char* dupLine = strdup(sanitized);

        char line2[strlen(sanitized) + 1];
        strncpy(line2, sanitized, strlen(sanitized));
        found = find_match_trie(sanitized, t, 1, lineNum, matches, found_token);

        if (found_token != NULL)
            wordlen = strlen(found_token);
        while (found != -1 && found + wordlen < read) {
            memset(sanitized, ' ', found + wordlen);
            found_token = NULL; // where to free found_token ?
            found = find_match_trie(sanitized, t, found + wordlen + 2,
             lineNum, matches, found_token);
            
            if (strncmp(sanitized, dupLine, strlen(sanitized)) != 0) {
                match* foundMatch = match_get_at_index(list_size(matches) - 1,
                 matches);

                match_set_line(foundMatch, dupLine);
            }

        }

        lineNum++;
        free(dupLine);
    }

    return matches;
}

void display_matches_batch(FILE *bp, list_t *matches)
{
	list_iterator_start(matches);               /* starting an iteration "session" */

	while (list_iterator_hasnext(matches)) {   // tell whether more values available
		match cur = *(match *)list_iterator_next(matches); /* get the next value */
		match_display(bp, &cur);
	}
	list_iterator_stop(matches);
}

void search_batch(FILE *fileptr, FILE *batchptr, trie_t *words_trie)
{
    list_t matches;
    list_init(&matches);
    matches = *find_matches_batch(fileptr, words_trie, &matches);
    display_matches_batch(batchptr, &matches);
}

void display_prev_match(list_t* matches, int index) {

    if (index == 0) {
        printf("\n...search hit top, continuing at bottom...\n\n");
    }
    
    match_display(stdout, match_prev(index, matches));
}


void display_next_match(list_t* matches, int index, FILE* pf, trie_t* words, int* section) {

    
    if (index == list_size(matches) - 1 && feof(pf)) {
        printf("\n...search hit bottom, continuing at top...\n\n");
    } else if (index == list_size(matches) - 1 && !feof(pf)) {
        printf("\n...looking for more matches...\n\n");
        parse_file_buffered(pf, section, words, matches);
    }
    match_display(stdout, match_next(index, matches));
}
