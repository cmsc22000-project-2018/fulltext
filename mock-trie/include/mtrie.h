// Sprint 2 Mock Trie Implementation
// Ruolin Zheng


// minimal C implementation of a mock trie

#ifndef __TRIE_H__
#define __TRIE_H__
 
// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)
 
typedef struct trie_t
{
	char *value;
    struct trie_t *children[ALPHABET_SIZE];
} trie_t;


// Returns 1 if key presents in trie, else 0
bool is_key_in_trie(trie_t *t, const char *key);

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
trie_t *trie_insert(trie_t *t, const char *key);

// Returns number of prefix matches
int num_matches(trie_t *t, const char *key);

// Prints out content of trie
void trie_show(trie_t *t);

// Mock integration with match_t, returns string of matches
char *return_matches_m(trie_t *trie, const char *key);

// Integration with match_t
// Returns a list of matches if key in trie, else NULL
// match_t *return_matches(trie_t *trie, const char *key);

#endif  /* __TRIE_H__  */
 
