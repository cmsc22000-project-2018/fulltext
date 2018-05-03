#include <stdlib.h>
#include "mtrie.h"

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