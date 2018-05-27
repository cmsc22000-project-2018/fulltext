/*
   A trie data structure
*/

#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "trie.h"
#include "utils.h"

/* See trie.h */
trie_t *trie_new(char current)
{
    trie_t *t = calloc(1,sizeof(trie_t));

    if (t == NULL){
        error("Could not allocate memory for trie_t");
        return NULL;
    } 

    t->current = current;

    t->children = calloc(256,sizeof(trie_t*));
    if (t->children == NULL){
        error("Could not allocate memory for t->children");
        return NULL;
    }

    t->is_word = 0;
    t->parent = NULL;

    return t;
}

/* See trie.h */
int trie_free(trie_t *t)
{
    assert( t != NULL);

    int i = 0;
    for (i=0; i<256; i++ ){
        if (t->children[i] !=NULL)
            trie_free(t->children[i]);
    }

    free(t);
    return 0;
}


/* See trie.h */
int trie_add_node(trie_t *t, char current)
{
    assert( t != NULL);

    unsigned c = (unsigned) current;

    if (t->children[c] == NULL)
        t->children[c] = trie_new(current);

    return 0;  

}

/* See trie.h */
int trie_insert_string(trie_t *t, char *word)
{
    assert(t!=NULL);

    if (*word == '\0'){
        t->is_word=1;
        return 0;

    } else {

        char curr = *word;

        int rc = trie_add_node(t, curr);
        if (rc != 0){
            error("Fail to add_node");
            return 1;
        }

        word++;
        return trie_insert_string(t->children[(unsigned)curr], word);
    }
}

int trie_from_stringarray(trie_t* t, char **strarr)
{
    int ret = 0;
    int i;
    for (i = 0; strarr[i] != NULL; i++) {
        ret = trie_insert_string(t, strarr[i]);
        if (ret == 1) return 1;
    }
    return 0;
}
