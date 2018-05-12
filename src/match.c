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
    int rc;
    
    if (m == NULL) 
    {
        printf("could not allocate memory for match\n");
        return NULL;
    }
    
    rc = init_match(m, word, line);
    if (rc != 0) 
    {
        printf("Could not init match word %s on line %d\n", word, line);
        return NULL;
    }

    return m;
}

int init_match(match* match, char* word, int line)
{
    if(match == NULL) return -1;

    match->word = word;
    match->line = line;
    
    return 0;
}

int free_match(match* match)
{
    if(match == NULL) return -1;
    free(match);
    return 0;
}

char* get_word(match* match)
{
    if(match == NULL) return NULL;
    return match->word;
}

int get_line(match* match)
{
    if(match == NULL) return -1;
    return match->line;
}

//changed inputs
match* next_match(match* match, GList* matches)
{
    if (match == NULL) return NULL;
    GList* cur = g_list_find(matches, match);
    if (cur->next == NULL) return (g_list_first(matches))->data;
    return (cur->next)->data;
}

//changed inputs
match* prev_match(match* match, GList* matches)
{
    if (match == NULL) return NULL;
    GList* cur = g_list_find(matches, match);
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
    return matches;
}

//changed inputs
match* get_at_index(int index, GList* matches)
{
    if (g_list_length(matches) == 0) return NULL;
    GList *toReturn = g_list_nth(matches, index);
    if (toReturn == NULL) return NULL;
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
        printf("list data: %s\n", (char*)list->data);
        list = next;
    }
    printf("\n");
}