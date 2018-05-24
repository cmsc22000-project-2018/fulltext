#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include "search.h"

int find_match(char* line, char* word, int pos_start, int lineNum)
{
    if (strlen(word) > strlen(line)) return -1;

    char* line2 = line;
    int pos = pos_start;
    char* token = strtok_r(line2, " ,.!?\r\t\n", &line2);

    while (token != NULL) {

        if (strcmp(token, word) == 0) {
            
            // create match
            // add to matches list

            printf("match found: %s at pos %d line %d\n", token, pos, lineNum);
            return pos;
        }

        pos += strlen(token) + 1;
        token = strtok_r(NULL, " ,.!?\r\t\n", &line2);

    }

    return -1;

}

void parse_file_buffered(FILE* pf, int start_line, int end_line, char* word)
{
    // logging
    printf("printing from lines %d to %d\n", start_line, end_line);

    char* line = NULL;
    int wordlen = strlen(word);
    size_t len = 0;
    ssize_t read;

    int found = -1;
    int lineNum = start_line;

    while (lineNum <= end_line && (read = getline(&line, &len, pf)) != -1) {
        // logging
        printf("\nline %d: %s", lineNum, line);

        char sanitized[strlen(line) + 1];
        strcpy(sanitized, line);
        sanitized[strcspn(sanitized, "\r\n")] = 0;

        char line2[strlen(sanitized) + 1];
        strcpy(line2, sanitized);
        found = find_match(sanitized, word, 1, lineNum);

        while (found != -1 && found + wordlen < read) {
            memset(sanitized, ' ', found + wordlen);
            found = find_match(sanitized, word, found + wordlen + 2, lineNum);
        }

        lineNum++;

    }
}

void display_prev_match(list_t* matches, match* curMatch) 
{
    /*
    1. get list and pointer to curr match
    2. get prev match (if curr match index = 0, go to last match)
    3. print out match details
    */
    match* prevMatch = prev_match(curMatch, matches);
    
    if (get_index(curMatch, matches) == 0) printf("...wrap-around to last match found...\n");

    printf("match: %s position %d line %d\n", prevMatch->word, prevMatch->position, prevMatch->line);

}

void display_next_match(list_t* matches, match* curMatch)
{
    /*
    1. get list and pointer to next match
    2. if pointer is NULL or (if wrap-around happened & EOF has not been reached yet), parse more
    3. else, print out match details
    */
    match* nextMatch = next_match(curMatch, matches);
    if (list_empty(matches) == 0 || get_index(nextMatch, matches) == 0) {
        printf("gotta read more in\n");
    } else {
        printf("match: %s position %d line %d\n", nextMatch->word, nextMatch->position, nextMatch->line);
    }

}