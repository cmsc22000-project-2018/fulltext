// Sprint 2 Mock Trie Implementation
// Ruolin Zheng

// minimal C implementation of a mock trie

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mtrie.h"

void trie_show(trie_t *trie)
{
    if (!trie || !trie->children[0])
        return;
    printf("%s\n", trie->children[0]->value);
    trie_show(trie->children[0]);
    printf("%s\n", trie->children[1]->value);
    trie_show(trie->children[1]);
    printf("%s\n", trie->children[2]->value);
    trie_show(trie->children[2]);
}

trie_t *trie_insert(trie_t *trie, const char *key)
{
    // a, b, c already present; return trie as it is
    if (strcmp(key, "a") == 0) return trie;
    if (strcmp(key, "b") == 0) return trie;
    if (strcmp(key, "c") == 0) return trie;

    if (strcmp(key, "an") == 0)
        return trie_insert_second_gen(trie, key); // second layer
    if (strcmp(key, "at") == 0)
        return trie_insert_second_gen(trie, key);
    return NULL; // does not fall in any case
}

trie_t *trie_insert_second_gen(trie_t *trie, const char *key)
{
    if (strcmp(key, "an") == 0) 
        trie->children[0]->children[0]->value = key;
    if (strcmp(key, "at") == 0)
        trie->children[0]->children[1]->value = key;
    return trie;
}

trie_t *trie_insert_third_gen(trie_t *trie, const char *key)
{
    if (strcmp(key, "an") == 0) 
        trie->children[0]->children[0]->value = key;
    if (strcmp(key, "at") == 0)
        trie->children[0]->children[1]->value = key;
    return trie;
}

int main()
{
    trie_t root;
    root.value = "";

    trie_t node_a;
    trie_t node_b;
    trie_t node_o;

    node_a.value = "a";
    node_b.value = "b";
    node_o.value = "o";

    root.children[0] = &node_a;
    root.children[1] = &node_b;
    root.children[2] = &node_o;

    trie_show(&root);

    
    return 0;
}