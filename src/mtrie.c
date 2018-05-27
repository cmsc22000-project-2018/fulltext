// Sprint 2 Mock Trie Implementation
// Ruolin Zheng

// Sprint 3 Mock Trie - Match Integration
// May 13, 2018

// minimal C implementation of a mock trie

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "simclist.h"
#include "mtrie.h"
#include "match.h"

// Returns 1 if key presents in trie, else 0
bool is_key_in_trie(trie_t *unused_t, char *key)
{
	// just to silence warning
	trie_t *temp = unused_t;
	unused_t = temp;
    if (strncmp(key, "a", 1) == 0) return 1;
    if (strncmp(key, "an", 2) == 0) return 1;
    if (strncmp(key, "and", 3) == 0) return 1;
    if (strncmp(key, "at", 2) == 0) return 1;
    if (strncmp(key, "b", 1) == 0) return 1;
    if (strncmp(key, "be", 2) == 0) return 1;
    else return 0;
}

// Three helpers for trie_insert
// Specific insert for second layer; two-char string
trie_t *trie_insert_len_one(trie_t *trie, char *key)
{
    if (strncmp(key, "o", 1) == 0)
        trie->children[2]->value = key;
    return trie;
}

// Specific insert for second layer; two-char string
trie_t *trie_insert_len_two(trie_t *trie, char *key)
{
    if (strncmp(key, "of", 2) == 0) {
        trie->children[2]->children[0]->value = key;
    }
    return trie;
}

// Specific insert for second layer; two-char string
trie_t *trie_insert_len_three(trie_t *trie, char *key)
{
    if (strncmp(key, "off", 3) == 0) {
        trie->children[2]->children[0]->
        children[0]->value = key;
    }
    if (strncmp(key, "bee", 3) == 0) {
        trie->children[1]->children[0]->
        children[0]->value = key;
    }
    return trie;
}

// If not present, inserts key into trie
// for minimal implementation, return NULL if key present
trie_t *trie_insert(trie_t *trie, char *key)
{
    if (strncmp(key, "o", 1) == 0) {
        return trie_insert_len_one(trie, key);
    }
    if (strncmp(key, "of", 2) == 0) {
        trie_t *result = trie_insert_len_one(trie, "o");
        return trie_insert_len_two(result, key);
    }
    if (strncmp(key, "off", 3) == 0) {
        trie_t *result = trie_insert_len_one(trie, "o");
        result = trie_insert_len_two(result, "of");
        return trie_insert_len_three(result, key);
    }
    if (strncmp(key, "bee", 3) == 0) {
        return trie_insert_len_three(trie, key);
    }
    return NULL;
}

// Returns number of prefix matches
int num_matches(trie_t *unused_t, char *key)
{
	trie_t *temp = unused_t;
	unused_t = temp;
    if (strncmp(key, "a", 1) == 0) return 4;
    if (strncmp(key, "an", 2) == 0) return 2;
    if (strncmp(key, "and", 3) == 0) return 1;
    if (strncmp(key, "at", 2) == 0) return 1;
    if (strncmp(key, "b", 1) == 0) return 2;
    if (strncmp(key, "be", 2) == 0) return 1;
    else return 0;
}

// Mock integration with match_t, returns string of matches
char *return_matches_m(trie_t *unused_t, char *key)
{
	trie_t *temp = unused_t;
	unused_t = temp;

    char *list = NULL;
    if (strncmp(key, "a", 1) == 0) list = "a, an, and, at";
    if (strncmp(key, "an", 2) == 0) list = "an, and";
    if (strncmp(key, "and", 3) == 0) list = "and";
    if (strncmp(key, "at", 2) == 0) list = "at";
    if (strncmp(key, "b", 1) == 0) list = "b, be";
    if (strncmp(key, "be", 2) == 0) list = "be";
    return list;
}

// Integration with match
// Returns: pointer of GList representing list of all matches
// 
// Ordering Issue:
// Text: and there was an ant; searches for 'an'
// GList: and->an->ant
// rank according to relative position in text or alphabetically?
list_t return_matches(trie_t *trie, char *key)
{
    // just to silence warning
    trie_t *temp = trie;
    trie = temp;

    list_t result;
    list_init(&result);
    // a->an->at->and
    if (strncmp(key, "a", 1) == 0) {
        match *m_a = match_new("a", 1, 1, "a line");
        match *m_an = match_new("an", 2, 1, "an line");
        match *m_at = match_new("at", 2, 1, "at line");
        match *m_and = match_new("and", 3, 1, "and line");
        
        match_append_(m_a, &result);
        match_append_(m_an, &result);
        match_append_(m_at, &result);
        match_append_(m_and, &result);
        
    }
    // an->and
    if (strncmp(key, "an", 2) == 0) {
        match *m_an = match_new("an", 2, 1, "an line");
        match *m_and = match_new("and", 3, 1, "and line");
        
        match_append_(m_an, &result);
        match_append_(m_and, &result);
    }
    if (strncmp(key, "and", 3) == 0) {
        match *m_and = match_new("and", 3, 1, "and line");
        match_append_(m_and, &result);
    } 
    if (strncmp(key, "at", 2) == 0) {
        match *m_at = match_new("at", 2, 1, "at line");
        match_append_(m_at, &result);
    }
    if (strncmp(key, "b", 1) == 0) {
        match *m_b = match_new("b", 1, 1, "b line");
        match *m_be = match_new("be", 2, 1, "be line");
        match_append_(m_b, &result);
        match_append_(m_be, &result);
    }
    if (strncmp(key, "be", 2) == 0) {
        match *m_be = match_new("be", 2, 1, "be line");
        match_append_(m_be, &result);
    }

    return result;
} 

// Prints out content of trie
void trie_show(trie_t *trie)
{
    if (!trie) return;
    if (!trie->children[0]) return;
    printf("%s\n", trie->children[0]->value);
    trie_show(trie->children[0]);
    if (!trie->children[1]) return;
    printf("%s\n", trie->children[1]->value);
    trie_show(trie->children[1]);
    if (!trie->children[2]) return;
    printf("%s\n", trie->children[2]->value);
    trie_show(trie->children[2]);
}
