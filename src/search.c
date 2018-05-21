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

void print_match(char *line, char *word, int line_num, int pos, long int filepos)
{
	printf("word: %s\nline %d pos %d fp %lu:\n%s\n", 
		word, line_num, pos, filepos, line);
}

// returns 0 when EOF
int read_until_next_match(FILE *pf, char *word, int line_num)
{
    char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	int pos = 0;
	long int filepos = 0;
	char *token, *saveptr, *saveln;

    while ((read = getline(&line, &len, pf)) != -1) {
    	saveln = strdup(line);
    	token = strtok_r(line, " ,.!?\t\n", &saveptr);
		while (token != NULL) {
			pos++;
			if (strncmp(word, token, strlen(word)) == 0) {
				filepos = ftell(pf);
				print_match(saveln, word, line_num, pos, filepos);
			}
			token = strtok_r(NULL, " ,.!?\t\n", &saveptr);			
		}
		free(saveln);
	}
	return 0;
}

