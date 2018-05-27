#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simclist.c"
#include "simclist.h"
#include "match.h"

/* See match.h for descriptions of functions */

match* new_match(char* word, int lineNum, int position, char* line)
{
	match* m = malloc(sizeof(match));
	int rc;
	if (m == NULL)
	{
		printf("could not allocate memory for match\n");
		return NULL;
	}

	rc = init_match(m, word, lineNum, position, line);
	if (rc != 0)
	{
		printf("Could not init match word %s on line [%d] position %d\n", word, lineNum, position);
		return NULL;
	}

	return m;
}

int init_match(match* match, char* word, int lineNum, int position, char* line)
{
	if (match == NULL) return -1;

	match->word = strdup(word);
	match->lineNum = lineNum;
	match->position = position;
	match->line = strdup(line);

	return 0;
}

int set_line(match* match, char* line)
{
	if (match == NULL) return -1;

	match->line = strdup(line);
	return 0;
}

int free_match(match* match)
{
	if (match == NULL) return -1;

	if (match->word != NULL) free(match->word);
	if (match->line != NULL) free(match->line);

	free(match);

	return 0;
}
char* get_word(match* match)
{
	if (match == NULL) return NULL;
	return match->word;
}

char* get_line(match* match)
{
	if (match == NULL) return NULL;
	return match->line;
}

int get_line_num(match* match)
{
	if (match == NULL) return -1;
	return match->lineNum;
}

int get_position(match* match)
{
	if (match == NULL) return -1;
	return match->position;
}


match* next_match(match* match, list_t* matches)
{
	if (match == NULL) return NULL;
	int rc = list_locate(matches, match);
	if (rc < 0) return NULL;
	int size = list_size(matches);
	return list_get_at(matches, (rc + 1) % size);
}


match* prev_match(match* match, list_t* matches)
{
	if (match == NULL) return NULL;
	int rc = list_locate(matches, match);
	if (rc < 0) return NULL;
	int size = list_size(matches);
	return list_get_at(matches, ((rc - 1) + size) % size);
}


void insert_at(match* newMatch, int index, list_t* matches)
{
	if (index > (int) (list_size(matches) - 1))
	{
		list_append(matches, newMatch);
	}
	if (index < 0)
	{
		list_prepend(matches, newMatch);
	}
	list_insert_at(matches, newMatch, index);
}


void append_(match* newMatch, list_t* matches)
{
    list_append(matches, newMatch);
}


void remove_at(int index, list_t* matches)
{
	list_delete_at(matches, index);
}


match* get_at_index(int index, list_t* matches)
{
	if (list_size(matches) == 0) return NULL;
	match* cur = list_get_at(matches, index);
	return cur;
}


int get_index(match* match, list_t* matches)
{
	int position = list_locate(matches, match);
	return position;
}

void info_list(list_t* l)
{
	printf("\n");
	printf("... displaying info about list ...\n");
	printf("The list now holds %u elements:\n", list_size(l));

	list_iterator_start(l);               /* starting an iteration "session" */

	while (list_iterator_hasnext(l)) {   // tell whether more values available
		match cur = *(match *)list_iterator_next(l); /* get the next value */
		display_match(&cur);
	}

	list_iterator_stop(l);                 /* ending the iteration "session" */

	printf("... finished ...\n");
}


void red() {
	printf("\033[1;31m");
}


void def() {
	printf("\033[0m");
}


void print_line(match* match)
{
	int i = 0;
	int wl = 0;

	char* w = get_word(match);
	char* s = get_line(match);

	while (w[wl] != '\0') wl++;

	while (s[i] != '\0') {
		if (i == get_position(match) - 1) red();
		else if (i == get_position(match) + wl) def();

		printf("%c", s[i]);
		i++;
	}

	printf("\n");
}


int display_match(match* match)
{
	if (match != NULL) {
		printf("> word: %s\n", get_word(match));
		printf("  [%d]: ", get_line_num(match));
		print_line(match);
		printf("   pos: %d\n", get_position(match));
		return 1;
	}

	printf("Match is empty\n");
	return -1;
}

