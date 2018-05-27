/*
   A trie data structure
*/

#ifndef _INCLUDE_TRIE_H_
#define _INCLUDE_TRIE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "parser.h"

typedef struct trie_t trie_t;
struct trie_t {
    // The first trie_t will be '/0/' for any Trie.
    char current;
    // ALPHABET_SIZE is 256 for all possible characters.
    trie_t **children;
    // if is_word is 1, indicates that this is the end of a word. Otherwise
    int is_word;
    // parent trie_t for traversing backwards
    trie_t *parent;
};

/*
   Creates and allocates memory for new trie_t.

Parameters:
- current: A char for the current character

Returns:
- A pointer to the trie, or NULL if a pointer
cannot be allocated
*/
trie_t *trie_new(char current);

/*
   Free an entire trie.
Parameters:
- t: A trie pointer

Returns:
- Always returns 0
*/
int trie_free(trie_t *t);


/*
   Creates new node in trie_t.
Parameters:
- current: A char indicating the character of the node being added
- t: A pointer to the trie where the node is to be added

Returns:
- 0 on success, 1 if an error occurs.
Details:
- Set t->children[current] to be current
- is_word for new node set to 0.
*/
int trie_add_node(trie_t *t, char current);

/*
   Inserts word into trie.
Parameters:
- word: An char array to be inserted into the given trie
- t: A pointer to the given trie

Returns:
- 0 on success, 1 if error occurs.

Details:
- For each trie, check if entry of the next character exists in the children array:
- If so, move into that node in the array
- If not, add a new node and move into that node in the array
- Then move on to the next character in string
- Set the is_word of the last node to 1
*/
int trie_insert_string(trie_t *t, char *word);

/*
   Delete word in trie.
Parameters:
- word: A char array to be deleted from the given trie
- t: A pointer to the given trie
Returns:
- 1 if deleted
Details:
- If word is not in trie
trie is not modified.
- If word is completely unique (no other part of the word is part of another word)
delete the entire word.
- If word is the prefix of another word in the trie
unmark the leaf node.
- If word is present in the trie, having at least one other word as a prefix,
delete all the nodes up to the prefix.
*/
int trie_delete_string(trie_t *t, char *word);

/*
   Search for a word in a trie.
Details: Returns 1 if word is found. Returns 0 if word is not found at all and -1 if word is found but end node's is_word is 0.
*/
int trie_search(char *word, trie_t *t);

int trie_from_stringarray(trie_t *t, char **strarray);
#endif
