// Unit tests for Mock Trie
// Updated May 16, return_matches integrated with simclist

#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "simclist.h"
#include "mtrie.h"
#include "match.h"

void check_is_key_in_trie(trie_t *unused, char *key, bool expected)
{
        bool result = is_key_in_trie(unused, key);
	cr_assert_eq(result, expected, 
		"%s is %s trie but got %s",
                key,
		result ? "in " : "not in ",
		expected ? "in" : "not in");
}

Test(trie, key_in_trie)
{
	trie_t unused;
	check_is_key_in_trie(&unused, "a", 1);
	check_is_key_in_trie(&unused, "an", 1);
	check_is_key_in_trie(&unused, "and", 1);
	check_is_key_in_trie(&unused, "at", 1);
	check_is_key_in_trie(&unused, "b", 1);
	check_is_key_in_trie(&unused, "be", 1);
}

Test(trie, not_key_in_trie)
{
	trie_t unused;
	check_is_key_in_trie(&unused, "ant", 0);
	check_is_key_in_trie(&unused, "bee", 0);
	check_is_key_in_trie(&unused, "o", 0);
	check_is_key_in_trie(&unused, "of", 0);
	check_is_key_in_trie(&unused, "off", 0);
	check_is_key_in_trie(&unused, "z", 0);
}

char *get_inserted_key(trie_t *trie, char *key)
{
  
	if (!trie || !trie->children) return NULL;
	if (strcmp(key, "bee") == 0) {
		if (trie->children[1]->children[0]->
        children[0])
			return trie->children[1]->children[0]->
        		children[0]->value;
	}
	if (strcmp(key, "off") == 0) {
		if (trie->children[2]->children[0]->
        children[0])
			return trie->children[2]->children[0]->
        		children[0]->value;
	}
	if (strcmp(key, "of") == 0) {
		 if (trie->children[2]->children[0]){
			 return trie->children[2]->children[0]->value;
     }
	}
	if (strcmp(key, "o") == 0) {
		if (trie->children[2])
			return trie->children[2]->value;
	}
	return NULL;
}

void check_trie_insert(trie_t *trie, char *key, char *expected)
{
	trie = trie_insert(trie, key);
	char *result = get_inserted_key(trie, key);
	cr_assert_not_null(result, "inserted %s, expected %s, but got NULL", key, expected);
	cr_assert_str_eq(result, expected,"inserted %s, expected %s, but got %s", key, expected, result);
}

Test(trie, insert_success)
{
	trie_t root;
    root.value = "";

    trie_t node_a, node_b, node_o;
    trie_t node_an, node_and, node_at;
    trie_t node_be, node_bee;
    trie_t node_of, node_off;

    node_a.value = "a";
    node_b.value = "b";
    node_o.value = NULL;

    root.children[0] = &node_a;
    root.children[1] = &node_b;
    root.children[2] = &node_o;

    node_an.value = "an";
    node_and.value = "and";
    node_at.value = "at";

    node_a.children[0] = &node_an;
    node_a.children[1] = &node_at;
    node_an.children[0] = &node_and;

    node_be.value = "be";
    node_bee.value = NULL;
    node_b.children[0] = &node_be;
    node_be.children[0] = &node_bee;

    node_of.value = NULL;
    node_off.value = NULL;
    node_o.children[0] = &node_of;
    node_of.children[0] = &node_off;

    //check_trie_insert(&root, "bee", "bee");
    //check_trie_insert(&root, "off", "off");
    check_trie_insert(&root, "of", "of");
    check_trie_insert(&root, "o", "o");

}

void check_no_insert(trie_t *trie, char *key)
{
	trie_t *result = trie_insert(trie, key);
	cr_assert_null(result, "%s already in trie but "
		"trie_insert fails to return NULL", key);
}

Test(trie, no_insert)
{
	trie_t root;

	check_no_insert(&root, "a");
	check_no_insert(&root, "an");
	check_no_insert(&root, "and");
	check_no_insert(&root, "at");
	check_no_insert(&root, "b");
	check_no_insert(&root, "be");

}

void check_num_matches(trie_t *trie, char *key, int expected)
{
	int result = num_matches(trie, key);
	cr_assert_eq(result, expected,
		"with key %s, expected %d matches, got %d",
		key, expected, result);
}

Test(trie, num_matches)
{
	trie_t root;
	check_num_matches(&root, "a", 4);
	check_num_matches(&root, "an", 2);
	check_num_matches(&root, "and", 1);
	check_num_matches(&root, "at", 1);
	check_num_matches(&root, "b", 2);
	check_num_matches(&root, "be", 1);

}

void check_return_matches_m(trie_t *trie, char *key, char *expected)
{
	char *result = return_matches_m(trie, key);
	cr_assert_not_null(result, 
		"inserted %s, expected %s, but got NULL",
		key, expected);
	cr_assert_str_eq(result, expected,
		"inserted %s, expected %s, but got %s",
		key, expected, result);
}

Test(trie, return_matches_mock)
{
	trie_t root;
	check_return_matches_m(&root, "a", "a, an, and, at");
	check_return_matches_m(&root, "an", "an, and");
	check_return_matches_m(&root, "and", "and");
	check_return_matches_m(&root, "at", "at");
	check_return_matches_m(&root, "b", "b, be");
	check_return_matches_m(&root, "be", "be");

}

void check_single_match(list_t matches, int index, char *expectedWord, int expectedLine)
{
    match* aRet = list_get_at(&matches, index);
    cr_assert_str_eq(expectedWord, aRet->word, "Expected word %s but got %s", expectedWord, aRet->word);
    cr_assert_eq(expectedLine, aRet->lineNum,"Expected line %d but got %d", expectedLine, aRet->lineNum);
}

void check_return_matches_listT(trie_t *trie, char *key, list_t *expected)
{
    list_t matches = return_matches(trie, key);
    if (strcmp(key, "a") == 0) {
	// a->an->at->and
	check_single_match(matches, 0, "a", 1);
	check_single_match(matches, 1, "an", 2);
	check_single_match(matches, 2, "at", 2);
	check_single_match(matches, 3, "and", 3);
    }
    if (strcmp(key, "an") == 0) {
        check_single_match(matches, 0, "an", 2);
	check_single_match(matches, 1, "and", 3);
    }
    if (strcmp(key, "and") == 0) {
		check_single_match(matches, 0, "and", 3);
    } 
    if (strcmp(key, "at") == 0) {
		check_single_match(matches, 0, "at", 2);
    }
    if (strcmp(key, "b") == 0) {
		check_single_match(matches, 0, "b", 1);
		check_single_match(matches, 1, "be", 2);
    }
    if (strcmp(key, "be") == 0) {
		check_single_match(matches, 0, "be", 2);
    }

}

Test(trie, return_matches_integrated_w_match)
{
    trie_t root;
    
    list_t matches_a_an_at_and, matches_an_and, matches_and, matches_at, matches_b_be, matches_be;

    list_init(&matches_a_an_at_and);
    list_init(&matches_an_and);
    list_init(&matches_and);
    list_init(&matches_at);
    list_init(&matches_b_be);
    list_init(&matches_be);
    
    match *m_a = match_new("a", 1, 1, "a line");
    match *m_an = match_new("an", 2, 1, "an line");
    match *m_at = match_new("at", 2, 1, "at line");
    match *m_and = match_new("and", 3, 1, "and line");
    match *m_b = match_new("b", 1, 1, "b line");
    match *m_be = match_new("be", 2, 1, "be line");
     
    match_append_(m_a, &matches_a_an_at_and);
    match_append_(m_an, &matches_a_an_at_and);
    match_append_(m_at, &matches_a_an_at_and);
    match_append_(m_and, &matches_a_an_at_and);
    
    match_append_(m_an, &matches_an_and);
    match_append_(m_and, &matches_an_and);
    
    match_append_(m_and, &matches_and);
    
    match_append_(m_at, &matches_at);
    
    match_append_(m_b, &matches_b_be);
    match_append_(m_be, &matches_b_be);
    
    match_append_(m_be, &matches_be);

    check_return_matches_listT(&root, "a", &matches_a_an_at_and);
    check_return_matches_listT(&root, "an", &matches_an_and);
    check_return_matches_listT(&root, "and", &matches_and);
    check_return_matches_listT(&root, "at", &matches_at);
    check_return_matches_listT(&root, "b", &matches_b_be);
    check_return_matches_listT(&root, "be", &matches_be);
}
