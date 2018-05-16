#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "simclist.h"
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
    list_t matches;
    list_init(&matches);
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    //using lib functions to test instead of ones written in match.c
    list_append(matches, a);
    list_append(matches, b);
    list_append(matches, c);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* nextMatch = next_match(a, matches);
    
    cr_assert_eq(nextMatch, b, "Expected %s but got %s", b->word, nextMatch->word);
}

/* Testing next_match for wraparound*/
Test(match, next_match_wraparound)
{
    list_t matches;
    list_init(&matches);
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    //using lib functions to test instead of ones written in match.c
    list_append(matches, a);
    list_append(matches, b);
    list_append(matches, c);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* nextMatch = next_match(c, matches);
    
    cr_assert_eq(nextMatch, a, "Expected %s but got %s", a->word, nextMatch->word);
}

/* Testing prev_match() in a regular case */
Test(match, prev_match_regular)
{
    list_t matches;
    list_init(&matches);
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    //using lib functions to test instead of ones written in match.c
    list_append(matches, a);
    list_append(matches, b);
    list_append(matches, c);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* prevMatch = prev_match(c, matches);
    
    cr_assert_eq(prevMatch, b, "Expected %s but got %s", b->word, prevMatch->word);
}

/* Testing prev_match for wraparound*/
Test(match, prev_match_wraparound)
{
    list_t matches;
    list_init(&matches);
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    //using lib functions to test instead of ones written in match.c
    list_append(matches, a);
    list_append(matches, b);
    list_append(matches, c);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* prevMatch = prev_match(a, matches);
    
    cr_assert_eq(prevMatch, c, "Expected %s but got %s", c->word, prevMatch->word);
}

/* Testing insert_at() for normal input*/
Test(match, insert_at_regular)
{
    list_t matches;
    list_init(&matches);
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    //using lib functions to test instead of ones written in match.c
    list_append(matches, a);
    list_append(matches, b);
    list_append(matches, c);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* toInsert = new_match("d", 1);
    
    insert_at(toInsert, 2, matches);
    
    match* cur = list_get_at(matches, 2);
    cr_assert_eq(cur, toInsert, "Expected %s but got %s", toInsert->word, cur->word);
}

/* Testing insert_at() for negative input*/
Test(match, insert_at_negative)
{
    list_t matches;
    list_init(&matches);
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    //using lib functions to test instead of ones written in match.c
    list_append(matches, a);
    list_append(matches, b);
    list_append(matches, c);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* toInsert = new_match("d", 1);
    
    insert_at(toInsert, -1, matches);
    
    match* cur = list_get_at(matches, 3);
    cr_assert_eq(cur, toInsert, "Expected %s but got %s", toInsert->word, cur->word);
}

/* Testing insert_at() for too large input*/
Test(match, insert_at_large)
{
    list_t matches;
    list_init(&matches);
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    //using lib functions to test instead of ones written in match.c
    list_append(matches, a);
    list_append(matches, b);
    list_append(matches, c);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* toInsert = new_match("d", 1);
    
    insert_at(toInsert, 5, matches);
    
    match* cur = list_get_at(matches, 3);
    cr_assert_eq(cur, toInsert, "Expected %s but got %s", toInsert->word, cur->word);
}

/* Testing append_() function */
Test(match, append)
{
    list_t matches;
    list_init(&matches);
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    append_(a, matches);
    append_(b, matches);
    append_(c, matches);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* aRet = list_get_at(matches, 0);
    cr_assert_eq(aRet, a, "Expected %s but got %s", a->word, aRet->word);
    
    match* bRet = list_get_at(matches, 1);
    cr_assert_eq(bRet, b, "Expected %s but got %s", b->word, bRet->word);
    
    match* cRet = list_get_at(matches, 2);
    cr_assert_eq(cRet, c, "Expected %s but got %s", c->word, cRet->word);
}

/* Testing remove_at for valid input */
Test(match, remove_at_valid)
{
    list_t matches;
    list_init(&matches);
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    append_(a, matches);
    append_(b, matches);
    append_(c, matches);
    
    cr_assert_not_null(matches, "matches is null");
    
    remove_at(0, matches);
    
    /*GList* firstItem = g_list_first(matches);
    match* first = firstItem->data;
    
    cr_assert_eq(first, b, "Expected first to be %s but got %s", b->word, first->word);*/
}

/* Testing remove_at for invalid input */
Test(match, remove_at_invalid)
{
    list_t matches;
    list_init(&matches);
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    append_(a, matches);
    append_(b, matches);
    append_(c, matches);
    
    cr_assert_not_null(matches, "matches is null");
    
    remove_at(3, matches);
    
    match* aRet = list_get_at(matches, 0);
    cr_assert_eq(aRet, a, "Expected %s but got %s", a->word, aRet->word);
    
    match* bRet = list_get_at(matches, 1);
    cr_assert_eq(bRet, b, "Expected %s but got %s", b->word, bRet->word);
    
    match* cRet = list_get_at(matches, 2);
    cr_assert_eq(cRet, c, "Expected %s but got %s", c->word, cRet->word);
}

/* Testing get_at_index for valid input */
Test(match, get_at_index_valid)
{
    list_t matches;
    list_init(&matches);
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    append_(a, matches);
    append_(b, matches);
    append_(c, matches);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* getA = get_at_index(0, matches);
    
    cr_assert_eq(getA, a, "Expected %s but got %s", a->word, getA->word);
}

/* Testing get_at_index for invalid input */
Test(match, get_at_index_invalid)
{
    list_t matches;
    list_init(&matches);
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    append_(a, matches);
    append_(b, matches);
    append_(c, matches);
    
    cr_assert_not_null(matches, "matches is null");
    
    match* getN = get_at_index(3, matches);
    
    cr_assert_null(getN, "Expected null but got %s", getN->word);
}

/* Testing get_index for valid input */
Test(match, get_index_valid)
{
    list_t matches;
    list_init(&matches);
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    append_(a, matches);
    append_(b, matches);
    append_(c, matches);
    
    cr_assert_not_null(matches, "matches is null");
    
    int index = get_index(a, matches);
    
    cr_assert_eq(index, 0, "Expected 0 but got %d", index);
}

/* Testing get_index for invalid inputs */
Test(match, get_index_invalid)
{
    list_t matches;
    list_init(&matches);
    
    match* a = new_match("a", 1);
    match* b = new_match("b", 1);
    match* c = new_match("c", 1);
    
    append_(a, matches);
    append_(b, matches);
    append_(c, matches);
    
    cr_assert_not_null(matches, "matches is null");
    
    int index = get_index(d, matches);
    
    cr_assert_eq(index, -1, "Expected -1 but got %d", index);
}