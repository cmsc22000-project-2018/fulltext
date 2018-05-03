#include "match.h"

/* See match.h for descriptions of functions */

match* new_match(char* word, int line)
{

}

void init_match(match* match, char* word, int line)
{

}

void free_match(match* match)
{

}

char* get_word(match* match)
{
    return match->word;
}

int get_line(match* match)
{
    return match->line;
}

match* next_match(match* match)
{

}

match* prev_match(match* match)
{

}
//changed inputs
void insert_at(match* newMatch, int index, GList matches)
{
    matches = g_list_insert(matches, newMatch, index);
}

//changed inputs
void append(match* newMatch, GList matches)
{
    matches = g_list_append(matches, newMatch);
}

//changed inputs
void remove_at(int index, GList matches)
{
    //get element at position
    GList *toDelete = g_list_nth(matches, index);
    
    //remove position at element
    matches = g_list_delete_link(matches, toDelete);
}

//changed inputs
match* get_at_index(int index, GList matches)
{
    GList *toReturn = g_list_nth(matches, index);
    return toReturn -> data;
}

int get_index(match* match)
{
    int position = g_list_index(l, match);
    return position;
}