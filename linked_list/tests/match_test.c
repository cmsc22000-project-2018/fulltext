/*
 * Not an actual test file, just something to do a basic test with
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <gmodule.h>
#include "match.h"

int main() {
    match* one = new_match("one", 1);
    match* two = new_match("two", 2);
    match* three = new_match("three", 3);
    
    printf("%s\n", one->word);
    printf("%s\n", two->word);
    printf("%s\n", three->word);
    
    GList* matches = NULL;
    
    matches = append_(one, matches);
    matches = append_(two, matches);
    matches = append_(three, matches);
    
    pretty_print(matches);
    
    match* want = get_at_index(2, matches);
    printf("retrieved %s\n", want->word);
    
    free_match(one);
    free_match(two);
    free_match(three);
    return 0;
}