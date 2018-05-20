#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "simclist.c"
#include "simclist.h"
#include "match.h"

// see search.h
list_t *minimal_read_until_next_match(list_t *match_list, char *search_word,
	FILE *fp)
{	
	char *line = NULL;
	char *token, *saveptr;
	size_t len = 0;
	ssize_t read;

	int line_num = 0;
	int pos = 0;

	// the search_word has no previous matches
	if (match_list == NULL) {
		list_init(match_list);
	}

	while ((read = getline(&line, &len, fp)) != -1) {
		line_num++;

		token = strtok_r(line, " ,.!?\t\n", &saveptr);
		while (token != NULL) {
			pos++;
			token = strtok_r(NULL, " ,.!?\t\n", &saveptr);

			// inefficient search algorithm
			if (strncmp(search_word, token, strlen(search_word)) == 0) {
				match *match_node = new_match(search_word, line_num, pos);
				append_(match_node, match_list);
				printf("line %d pos %d  %s\n", line_num, pos, token);
				return match_list;
			}

		}
	}
	printf("not found\n");
	return NULL;

}

int main()
{
<<<<<<< HEAD
	char buf[6];
	list_t *match_list = NULL;
    //list_init(match_list);
    FILE *fp = fopen("filetest.txt", "r");
    while ((fgets(buf, 6, stdin) != NULL)
				&& (strncmp(buf, "next", 4) == 0)) {
    	minimal_read_until_next_match(match_list, "fulltext", fp);
    }
}
=======
	list_t match_list;
    list_init(&match_list);
    match* a = new_match("a", 1, 1);
    match* b = new_match("b", 1, 1);

    list_append(&match_list, a);
    list_append(&match_list, b);

    match* nextMatch = next_match(a, &match_list);
    printf("%s\n", nextMatch->word);
}
>>>>>>> eb1b9b78a9bb6354113ecaf9ed1e71680dbc8ce0
