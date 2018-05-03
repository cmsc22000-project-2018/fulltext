// Sprint 2 Mock Trie Implementation
// Ruolin Zheng

// minimal C implementation of a mock trie

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "mtrie.h"

// Returns 1 if key presents in trie, else 0
bool is_key_in_trie(trie_t *unused_t, const char *key)
{
    if (strcmp(key, "a") == 0) return 1;
    if (strcmp(key, "an") == 0) return 1;
    if (strcmp(key, "and") == 0) return 1;
    if (strcmp(key, "at") == 0) return 1;
    if (strcmp(key, "b") == 0) return 1;
    if (strcmp(key, "be") == 0) return 1;
    else return 0;
}

// Three helpers for trie_insert
// Specific insert for second layer; two-char string
trie_t *trie_insert_len_one(trie_t *trie, const char *key)
{
    if (strcmp(key, "o") == 0)
        trie->children[2]->value = key;
    return trie;
}

// Specific insert for second layer; two-char string
trie_t *trie_insert_len_two(trie_t *trie, const char *key)
{
    if (strcmp(key, "of") == 0)
        trie->children[2]->children[0]->value = key;
    return trie;
}

// Specific insert for second layer; two-char string
trie_t *trie_insert_len_three(trie_t *trie, const char *key)
{
    if (strcmp(key, "off") == 0) {
        trie->children[2]->children[0]->
        children[0]->value = key;
    }
    if (strcmp(key, "bee") == 0) {
        trie->children[1]->children[0]->
        children[0]->value = key;
    }
    return trie;
}

// If not present, inserts key into trie
trie_t *trie_insert(trie_t *trie, const char *key)
{
    if (strcmp(key, "o") == 0)
        return trie_insert_len_one(trie, key);
    if (strcmp(key, "of") == 0) {
        trie_t *result = trie_insert_len_one(trie, "o");
        return trie_insert_len_two(result, key);
    }
    if (strcmp(key, "off") == 0) {
        trie_t *result = trie_insert_len_one(trie, "o");
        result = trie_insert_len_two(result, "of");
        return trie_insert_len_three(result, key);
    }
    if (strcmp(key, "bee") == 0)
        return trie_insert_len_three(trie, key);
    return NULL;
}

// Returns number of prefix matches
int num_matches(trie_t *unused_t, const char *key)
{
    if (strcmp(key, "a") == 0) return 4;
    if (strcmp(key, "an") == 0) return 2;
    if (strcmp(key, "and") == 0) return 1;
    if (strcmp(key, "at") == 0) return 1;
    if (strcmp(key, "b") == 0) return 2;
    if (strcmp(key, "be") == 0) return 1;
    else return 0;
}

// Mock integration with match_t, returns string of matches
char *return_matches_m(trie_t *unused_t, const char *key)
{
    char *list;
    if (strcmp(key, "a") == 0) list = "a, an, and, at";
    if (strcmp(key, "an") == 0) list = "an, and";
    if (strcmp(key, "and") == 0) list = "and";
    if (strcmp(key, "at") == 0) list = "a, at";
    if (strcmp(key, "b") == 0) list = "b, be";
    if (strcmp(key, "be") == 0) list = "be";
    return list;
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

int main()
{
    trie_t root;
    root.value = "";

    trie_t node_a;
    trie_t node_b;

    node_a.value = "a";
    node_b.value = "b";

    root.children[0] = &node_a;
    root.children[1] = &node_b;
    root.children[2] = NULL;

    printf("Initial Trie:\n");
    printf("eye-ball tests for trie_show\nexpect a, b\n");
    trie_show(&root);
    printf("\n");

    root = trie_insert(&root, "off");

    printf("Insert: off\n");
    printf("eye-ball tests for trie_show\nexpect a, b\n");
    trie_show(&root);

    printf("eye-ball tests for trie_show\nexpect a, b\n");
    trie_show(&root);
    
    return 0;
}