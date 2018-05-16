#include <stdio.h>
#include <stdlib.h>
#include "simclist.c"
#include "simclist.h"
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
match* next_match(match* match, list_t* matches)
{
    if (match == NULL) return NULL;
    int rc = list_locate(matches, match);
    if (rc < 0) return NULL;
    int size = list_size(matches);
    return list_get_at(matches, (rc + 1) % size);
}

//changed inputs
match* prev_match(match* match, list_t* matches)
{
    if (match == NULL) return NULL;
    int rc = list_locate(matches, match);
    if (rc < 0) return NULL;
    int size = list_size(matches);
    return list_get_at(matches, ((rc - 1) + size) % size);
}
//changed inputs, return type
void insert_at(match* newMatch, int index, list_t* matches)
{
    list_insert_at(matches, newMatch, index);
}

//changed inputs, return type
void append_(match* newMatch, list_t* matches)
{
    list_append(matches, newMatch);
}

//changed inputs, return type
void remove_at(int index, list_t* matches)
{
    list_delete_at(matches, index);  
}

//changed inputs
match* get_at_index(int index, list_t* matches)
{
    if (list_size(matches) == 0) return NULL;
    match* cur = list_get_at(matches, index);
    return cur;
}

//changed inputs
int get_index(match* match, list_t* matches)
{
    int position = list_locate(matches, match);
    return position;
}

//just for testing
void pretty_print(list_t* l)
{
    printf("\n");
    list_iterator_start(l);               /* starting an iteration "session" */
    while (list_iterator_hasnext(l)) { /* tell whether more values available */
        printf("%d\n", *(int *)list_iterator_next(l)); /* get the next value */
    }
    list_iterator_stop(l);                 /* ending the iteration "session" */
    printf("\n");
}
