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

    // Nothing has been found
    return false;

}

//in the case that string is not null-terminated
//this will prevent a segfault
#define MATCH_MAXLEN 100

list_t* parse_file_buffered(FILE* pf, int start_line, int end_line, char* word, list_t* matches) {

    char* line = NULL;
    int wordlen = strlen(word);
    size_t len = 0;
    ssize_t read;

    int found = false;
    int lineNum = start_line;

    while (lineNum <= end_line && (read = getline(&line, &len, pf)) != -1) {

        char sanitized[MATCH_MAXLEN + 1];
        strncpy(sanitized, line, MATCH_MAXLEN);
        sanitized[strcspn(sanitized, "\r\n")] = '\0';
        char* dupLine = strdup(sanitized);

        char line2[MATCH_MAXLEN + 1];
        strncpy(line2, sanitized, MATCH_MAXLEN);
        found = find_match(sanitized, word, 1, lineNum, matches);

        while (found != false && found + wordlen < read) {
            memset(sanitized, ' ', found + wordlen);
            found = find_match(sanitized, word, found + wordlen + 2, lineNum, matches);

            if (strncmp(sanitized, dupLine, MATCH_MAXLEN) != 0) {
                match* foundMatch = match_get_at_index(list_size(matches) - 1, matches);
                match_set_line(foundMatch, dupLine);
            }

        }

        lineNum++;
        free(dupLine);
    }

    return matches;
}

void display_prev_match(list_t* matches, int index) {
    if (index == 0) {
        printf("\n...search hit top, continuing at bottom...\n\n");
    }

    match_display(match_prev(index, matches));
}

void display_next_match(list_t* matches, int index) {

    if (index == list_size(matches) - 1) {
        printf("\n...search hit bottom, continuing at top...\n\n");
    }

    match_display(match_next(index, matches));

}
