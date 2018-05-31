#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include <simclist.h>
#include "search.h"
#include "match.h"

int find_match(char* line, char* word, int pos_start, int lineNum, list_t* matches) {
    if (strlen(word) > strlen(line)) return -1;

    char* dup = strdup(line);

    char* line2 = strdup(line);
    int pos = pos_start;
    char* token = strtok(line2, " ,.!?\r\t\n");
    match* foundMatch = NULL;

    while (token != NULL) {

        if (strncmp(token, word, strlen(word)) == 0) {

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

list_t* parse_file_buffered(FILE* pf, int start_line, int end_line, char* word, list_t* matches) {

    char* line = NULL;
    int wordlen = strlen(word);
    size_t len = 0;
    ssize_t read;

    int found = -1;
    int lineNum = start_line;

    while (lineNum <= end_line && (read = getline(&line, &len, pf)) != -1) {

        char sanitized[strlen(line) + 1];
        strncpy(sanitized, line, strlen(line));
        sanitized[strcspn(sanitized, "\r\n")] = 0;
        char* dupLine = strdup(sanitized);

        char line2[strlen(sanitized) + 1];
        strncpy(line2, sanitized, strlen(sanitized));
        found = find_match(sanitized, word, 1, lineNum, matches);

        while (found != -1 && found + wordlen < read) {
            memset(sanitized, ' ', found + wordlen);
            found = find_match(sanitized, word, found + wordlen + 2, lineNum, matches);

            if (strncmp(sanitized, dupLine, strlen(sanitized)) != 0) {
                match* foundMatch = match_get_at_index(list_size(matches) - 1, matches);
                match_set_line(foundMatch, dupLine);
            }

        }

        lineNum++;
        free(dupLine);
    }

    return matches;
}

void display_prev_match(list_t* matches, match* curMatch) {
    /*
    1. get list and pointer to curr match
    2. get prev match (if curr match index = 0, go to last match)
    3. print out match details
    */

    if (match_get_index(curMatch, matches) == 0) {
        printf("...wrap-around to last match found...\n");
    }

    curMatch = match_prev(curMatch, matches);

    match_display(curMatch);
}

/* NEEDS FIX */
void display_next_match(list_t* matches, match* curMatch) {
    /*
    1. get list and pointer to next match
    2. if pointer is NULL or (if wrap-around happened & EOF has not been reached yet), parse more
    3. else, print out match details
    */

    curMatch = match_next(curMatch, matches);
    if (match_get_index(curMatch, matches) == 0) {
        printf("...wrap-around to first match found...\n");
        // parse more
        // if EOF has been reached (how do we know that?),
        //  we say ...wrap-around to first match found...
        // else
        //  display next match

    } else {
        match_display(curMatch);
    }

}
