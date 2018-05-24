#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include "search.h"

int find_match(char* line, char* word, int pos_start, int lineNum, list_t* matches)
{
    if (strlen(word) > strlen(line)) return -1;

    char* line2 = line;
    int pos = pos_start;
    char* token = strtok_r(line2, " ,.!?\r\t\n", &line2);
    match* foundMatch = NULL;

    while (token != NULL) {

        if (strcmp(token, word) == 0) {

            foundMatch = new_match(word, lineNum, pos);
            append_(foundMatch, matches);

            // logging
            printf("match found: %s at pos %d line %d\n", token, pos, lineNum);

            return pos;
        }

        pos += strlen(token) + 1;
        token = strtok_r(NULL, " ,.!?\r\t\n", &line2);

    }

    return -1;

}

list_t* parse_file_buffered(FILE* pf, int start_line, int end_line, char* word, list_t* matches)
{

    char* line = NULL;
    int wordlen = strlen(word);
    size_t len = 0;
    ssize_t read;

    int found = -1;
    int lineNum = start_line;

    while (lineNum <= end_line && (read = getline(&line, &len, pf)) != -1) {

        char sanitized[strlen(line) + 1];
        strcpy(sanitized, line);
        sanitized[strcspn(sanitized, "\r\n")] = 0;

        char line2[strlen(sanitized) + 1];
        strcpy(line2, sanitized);
        found = find_match(sanitized, word, 1, lineNum, matches);

        while (found != -1 && found + wordlen < read) {
            memset(sanitized, ' ', found + wordlen);
            found = find_match(sanitized, word, found + wordlen + 2, lineNum, matches);
        }

        lineNum++;
    }

    return matches;
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

    display_match(prevMatch);

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

    } else {
        display_match(nextMatch);
    }

}