#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <gmodule.h>
#include "match.h"

/* See match.h for descriptions of functions */

match* new_match(char* word, int line)
{
    match* m = malloc(sizeof(match));
    
    if (m == NULL) return NULL;
    
    init_match(m, word, line);

    return m;
}

void init_match(match* match, char* word, int line)
{
    if (match == NULL) return;

    match->word = word;
    match->line = line;
}

void free_match(match* match)
{
    free(match);
}

char* get_word(match* match)
{
    return match->word;
}

int get_line(match* match)
{
    return match->line;
}

//changed inputs
match* next_match(match* match, GList* matches)
{
    GList* cur = g_list_find(matches, match->word);
    if (cur->next == NULL) return (g_list_first(matches))->data;
    return (cur->next)->data;
}

//changed inputs
match* prev_match(match* match, GList* matches)
{
    GList* cur = g_list_find(matches, match->word);
    if (cur->prev == NULL) return (g_list_last(matches))->data;
    return (cur->prev)->data;
}
//changed inputs, return type
GList* insert_at(match* newMatch, int index, GList* matches)
{
    matches = g_list_insert(matches, newMatch, index);
    return matches;
}

//changed inputs, return type
GList* append_(match* newMatch, GList* matches)
{
    matches = g_list_append(matches, newMatch);
    return matches;
}

//changed inputs, return type
GList* remove_at(int index, GList* matches)
{
    //get element at position
    GList *toDelete = g_list_nth(matches, index);
    
    //remove position at element
    matches = g_list_delete_link(matches, toDelete);
}

//changed inputs
match* get_at_index(int index, GList* matches)
{
    GList *toReturn = g_list_nth(matches, index);
    return toReturn -> data;
}

//changed inputs
int get_index(match* match, GList* matches)
{
    int position = g_list_index(matches, match);
    return position;
}

//just for testing
void pretty_print(GList* l)
{
    GList *list = l;
    while (list != NULL){
        GList *next = list->next;
        printf("list data: %s\n", list->data);
        list = next;
    }
    printf("\n");
}