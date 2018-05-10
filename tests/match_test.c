#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <gmodule.h>
#include "match.h"

/* Testing match new function */
Test (match, new) 
{
    match* m;
    
    m = new_match("one", 1);
    
    cr_assert_not_null(m, "new_match() failed");
    
    cr_assert_eq(m->word, "one", "new_match() word incorrect");
    cr_assert_eq(m->line, 1, "new_match() line incorrect");
}

/* Testing match init function*/
Test (match, init)
{
    match m;
    int rc;
    
    rc = init_match(&m, "one", 1);
    
    cr_assert_eq(rc, 0, "init_match failed");

    cr_assert_eq(m.word, "one", "init_match didn't set word");
    cr_assert_eq(m.line, 1, "init_match didn't set line");
}

/* Testing free_match() function */
Test(match, free) 
{
    match* m;
    int rc;

    m = new_match("one", 1);

    cr_assert_not_null(m, "new_match() failed");

    rc = free_match(m);

    cr_assert_eq(rc, 0, "free_match() failed");
}

/* Testing get_word() function */
void test_get_word(char* word, int line, char* exp)
{
    match m;
    
    init_match(&m, word, line);
    
    char* the_word = get_word(&m);
    
    cr_assert_eq(the_word, word, "Expected %s but got %s", exp, the_word);
}

Test(match, get_word)
{
    test_get_word("seven", 1, "seven");
    test_get_word("9", 1, "9");
    test_get_word(",", 1, ",");
}

/* Testing get_line() function */
void test_get_line(char* word, int line, int exp)
{
    match m;
    
    init_match(&m, word, line);
    
    int the_line = get_line(&m);
    
    cr_assert_eq(the_line, line, "Expected %d but got %d", exp, the_line);
}

Test(match, get_line)
{
    test_get_line("seven", 1, 1);
    test_get_line("9", 73, 73);
    test_get_line(",", -1, -1);
}

/* Testing next_match() in a regular case */
Test(match, next_match_regular)
{
    GList* matches = NULL;
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    //using lib functions to test instead of ones written in match.c
    matches = g_list_append(matches, a);
    matches = g_list_append(matches, b);
    matches = g_list_append(matches, c);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* nextMatch = next_match(a, matches);
    
    cr_assert_eq(nextMatch, b, "Expected %s but got %s", b->word, nextMatch->word);
}

/* Testing next_match for wraparound*/
Test(match, next_match_wraparound)
{
    GList* matches = NULL;
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    //using lib functions to test instead of ones written in match.c
    matches = g_list_append(matches, a);
    matches = g_list_append(matches, b);
    matches = g_list_append(matches, c);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* nextMatch = next_match(c, matches);
    
    cr_assert_eq(nextMatch, a, "Expected %s but got %s", a->word, nextMatch->word);
}

/* Testing prev_match() in a regular case */
Test(match, prev_match_regular)
{
    GList* matches = NULL;
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    //using lib functions to test instead of ones written in match.c
    matches = g_list_append(matches, a);
    matches = g_list_append(matches, b);
    matches = g_list_append(matches, c);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* prevMatch = prev_match(c, matches);
    
    cr_assert_eq(prevMatch, b, "Expected %s but got %s", b->word, prevMatch->word);
}

/* Testing prev_match for wraparound*/
Test(match, prev_match_wraparound)
{
    GList* matches = NULL;
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    //using lib functions to test instead of ones written in match.c
    matches = g_list_append(matches, a);
    matches = g_list_append(matches, b);
    matches = g_list_append(matches, c);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* prevMatch = prev_match(a, matches);
    
    cr_assert_eq(prevMatch, c, "Expected %s but got %s", c->word, prevMatch->word);
}

/* Testing insert_at() for normal input*/
Test(match, insert_at_regular)
{
    GList* matches = NULL;
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    //using lib functions to test instead of ones written in match.c
    matches = g_list_append(matches, a);
    matches = g_list_append(matches, b);
    matches = g_list_append(matches, c);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* toInsert = new_match("d", 1);
    
    matches = insert_at(toInsert, 2, matches);
    
    GList* retrieved = g_list_nth(matches, 2);
    match* fromRet = retrieved->data;
    
    cr_assert_eq(fromRet, toInsert, "Expected %s but got %s", toInsert->word, fromRet->word);
}

/* Testing insert_at() for negative input*/
Test(match, insert_at_negative)
{
    GList* matches = NULL;
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    //using lib functions to test instead of ones written in match.c
    matches = g_list_append(matches, a);
    matches = g_list_append(matches, b);
    matches = g_list_append(matches, c);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* toInsert = new_match("d", 1);
    
    matches = insert_at(toInsert, -1, matches);
    
    GList* retrieved = g_list_nth(matches, 3);
    match* fromRet = retrieved->data;
    
    cr_assert_eq(fromRet, toInsert, "Expected %s but got %s", toInsert->word, fromRet->word);
}

/* Testing insert_at() for too large input*/
Test(match, insert_at_large)
{
    GList* matches = NULL;
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    //using lib functions to test instead of ones written in match.c
    matches = g_list_append(matches, a);
    matches = g_list_append(matches, b);
    matches = g_list_append(matches, c);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* toInsert = new_match("d", 1);
    
    matches = insert_at(toInsert, 5, matches);
    
    GList* retrieved = g_list_nth(matches, 3);
    match* fromRet = retrieved->data;
    
    cr_assert_eq(fromRet, toInsert, "Expected %s but got %s", toInsert->word, fromRet->word);
}

/* Testing append_() function */
Test(match, append)
{
    GList* matches = NULL;
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    matches = append_(a, matches);
    matches = append_(b, matches);
    matches = append_(c, matches);
    
    cr_assert_not_null(matches, "matches is null");
    
    GList* aRet = g_list_nth(matches, 0);
    match* aFromRet = aRet->data;
    cr_assert_eq(aFromRet, a, "Expected %s but got %s", a->word, aFromRet->word);
    
    GList* bRet = g_list_nth(matches, 1);
    match* bFromRet = bRet->data;
    cr_assert_eq(bFromRet, b, "Expected %s but got %s", b->word, bFromRet->word);
    
    GList* cRet = g_list_nth(matches, 2);
    match* cFromRet = cRet->data;
    cr_assert_eq(cFromRet, c, "Expected %s but got %s", c->word, cFromRet->word);
}

/* Testing remove_at for valid input */
Test(match, remove_at_valid)
{
    GList* matches = NULL;
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    matches = append_(a, matches);
    matches = append_(b, matches);
    matches = append_(c, matches);
    
    cr_assert_not_null(matches, "matches is null");
    
    matches = remove_at(0, matches);
    
    GList* firstItem = g_list_first(matches);
    match* first = firstItem->data;
    
    cr_assert_eq(first, b, "Expected first to be %s but got %s", b->word, first->word);
}

/* Testing remove_at for invalid input */
Test(match, remove_at_invalid)
{
    GList* matches = NULL;
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    matches = append_(a, matches);
    matches = append_(b, matches);
    matches = append_(c, matches);
    
    cr_assert_not_null(matches, "matches is null");
    
    matches = remove_at(3, matches);
    
    GList* aRet = g_list_nth(matches, 0);
    match* aFromRet = aRet->data;
    cr_assert_eq(aFromRet, a, "Expected %s but got %s", a->word, aFromRet->word);
    
    GList* bRet = g_list_nth(matches, 1);
    match* bFromRet = bRet->data;
    cr_assert_eq(bFromRet, b, "Expected %s but got %s", b->word, bFromRet->word);
    
    GList* cRet = g_list_nth(matches, 2);
    match* cFromRet = cRet->data;
    cr_assert_eq(cFromRet, c, "Expected %s but got %s", c->word, cFromRet->word);
}

/* Testing get_at_index for valid input */
Test(match, get_at_index_valid)
{
    GList* matches = NULL;
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    matches = append_(a, matches);
    matches = append_(b, matches);
    matches = append_(c, matches);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* getA = get_at_index(0, matches);
    
    cr_assert_eq(getA, a, "Expected %s but got %s", a->word, getA->word);
}

/* Testing get_at_index for invalid input */
Test(match, get_at_index_invalid)
{
    GList* matches = NULL;
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    matches = append_(a, matches);
    matches = append_(b, matches);
    matches = append_(c, matches);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* getN = get_at_index(3, matches);
    
    cr_assert_null(getN, "Expected null but got %s", getN->word);
}

/* Testing get_index for valid input */
Test(match, get_index_valid)
{
    GList* matches = NULL;
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    matches = append_(a, matches);
    matches = append_(b, matches);
    matches = append_(c, matches);
    
    cr_assert_not_null(matches, "matches is null");
    
    int index = get_index(a, matches);
    
    cr_assert_eq(index, 0, "Expected 0 but got %d", index);
}

/* Testing get_index for invalid inputs */
Test(match, get_index_invalid)
{
    GList* matches = NULL;
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    match* d = new_match("d", 1);
    
    matches = append_(a, matches);
    matches = append_(b, matches);
    matches = append_(c, matches);
    
    cr_assert_not_null(matches, "matches is null");
    
    int index = get_index(d, matches);
    
    cr_assert_eq(index, -1, "Expected -1 but got %d", index);
}