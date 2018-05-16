// Sprint 2 Mock Trie Implementation
// Ruolin Zheng


// minimal C implementation of a mock trie
// Comment:
// Some functions, ex. num_of_matches was written 
// under the assumption that we need to support
// partial searches

#ifndef INCLUDE_FULLTEXT_TRIE_H_
#define INCLUDE_FULLTEXT_TRIE_H_
 
// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)
 
typedef struct trie_t
{
	char *value;
    struct trie_t *children[ALPHABET_SIZE];
} trie_t;

/**
    @brief Checks if given word is in trie.
    @param trie: the trie containing search terms.
    @param key: the word to be searched for.
    @return a boolean value, 1 if key in trie, else 0
 */
bool is_key_in_trie(trie_t *trie, char *key);

/**
    @brief Inserts the word into trie if it is not already in.
    @param trie: the trie containing search terms.
    @param key: the word to be inserted.
    @return the trie after insertion.
 */
// If not present, inserts key into trie
trie_t *trie_insert(trie_t *trie, char *key);

/**
    @brief Returns number of prefix matches
    @param trie: the trie containing search terms.
    @param key: the word to be checked against.
    @return an integer of match number.
 */
// Returns number of prefix matches
int num_matches(trie_t *trie, char *key);

/**
    @brief Prints out content of trie.
    @param trie of type trie_t.
    @return None.
 */
void trie_show(trie_t *trie);

/**
    @brief Mock integration with match class;
    @returns string of matches.
    @param trie 
    @param of type trie_t, searchkey of type string.
    @return matches in the form of a string
 */
char *return_matches_m(trie_t *trie, char *key);

/**
    @brief Integration with match; 
    @returns a list_t of matches if key in trie; NULL if no matches
    @param trie of type trie_t, search key of type string
 */
list_t return_matches(trie_t *trie, char *key);

#endif  /* INCLUDE_FULLTEXT_TRIE_H_  */
 
