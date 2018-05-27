#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "trie.h"

Test(trie, new)
{
    trie_t *t;

    t = trie_new('c');

    cr_assert_not_null(t, "trie_new() failed to allocate memory");
    cr_assert_eq(t->current, 'c', "trie_new() failed to set current");
    cr_assert_eq(t->is_word, 0, "trie_new() failed to set is_word");
}


Test(trie, trie_add_node_exists)
{
    char n = 'n';
    trie_t *t = trie_new('\0');
    int rc = trie_add_node(t,n);

    cr_assert_eq(rc,0,"trie_add_node failed");
    cr_assert_not_null(t->children[(unsigned)n], "trie_add_node failed to allocate new entry");
    cr_assert_eq(t->children[(unsigned)n]->current,n, "trie_add_node failed to set is_word for new trie");
    cr_assert_eq(t->children[(unsigned)n]->is_word,0, "trie_add_node failed to set is_word for new trie");
}

Test(trie, trie_add_node_new)
{
    char n = 'n';
    trie_t *t = trie_new('\0');

    int fc = trie_add_node(t,n);
    cr_assert_eq(fc,0,"trie_add_node failed");

    int rc = trie_add_node(t,n);

    cr_assert_eq(rc,0,"trie_add_node failed");
    cr_assert_not_null(t->children[(unsigned)n], "trie_add_node failed to allocate new entry");
    cr_assert_eq(t->children[(unsigned)n]->current,n, "trie_add_node failed to set is_word for new trie");
    cr_assert_eq(t->children[(unsigned)n]->is_word,0, "trie_add_node failed to set is_word for new trie");
}

Test(trie, trie_insert_string)
{
    char* s1 = "an";
    char* s2 = "anti";
    char* s3 = "ants";
    trie_t *t = trie_new('\0');

    int r1 = trie_insert_string(t,s1);
    cr_assert_eq(r1,0,"trie_insert_string failed");   
    cr_assert_not_null(t->children['a'], "trie_add_node failed to allocate new entry");
    cr_assert_eq(t->children['a']->is_word,0, "trie_add_node failed to set is_word for new trie");
    cr_assert_not_null(t->children['a']->children['n'] , "trie_add_node failed to allocate new entry");
    cr_assert_eq(t->children['a']->children['n']->is_word,1, "trie_insert_string failed to set is_word for end character");

    int r2 = trie_insert_string(t,s2);
    cr_assert_eq(r2,0,"trie_insert_string failed");
    cr_assert_eq(t->children['a']->children['n']->is_word,1, "trie_insert_string failed to set is_word for end character");
    cr_assert_eq(t->children['a']->children['n']->children['t']->children['i']->is_word,1, "trie_insert_string failed to set is_word for end character");

    int r3 = trie_insert_string(t,s3);
    cr_assert_eq(r3,0,"trie_insert_string failed");
    cr_assert_eq(t->children['a']->children['n']->children['t']->is_word,0, "trie_insert_string failed to set is_word for middle character");
    cr_assert_eq(t->children['a']->children['n']->children['t']->children['s']->is_word,1, "trie_insert_string failed to set is_word for end character");


}

Test(trie, free)
{
    trie_t *t;
    int rc;

    t = trie_new('\0');

    cr_assert_not_null(t, "trie_new() failed to allocate memory");

    rc = trie_free(t);

    cr_assert_eq(rc, 0, "trie_free failed");

}

Test(trie, trie_from_stringarray)
{
    char* s1 = "an";
    char* s2 = "anti";
    char* s3 = "ants";
    trie_t *t = trie_new('\0');

    char **strarray = malloc(4*sizeof(char*));
    strarray[0] = s1;
    strarray[1] = s2;
    strarray[2] = s3;
    strarray[3] = NULL;

    cr_assert_eq(strarray[1], "anti", "Failed to build strarray");

    int r = trie_from_stringarray(t, strarray);
    cr_assert_eq(r,0,"trie_insert_string failed");   
    cr_assert_not_null(t->children['a'], "trie_add_node failed to allocate new entry");
    cr_assert_eq(t->children['a']->is_word,0, "trie_add_node failed to set is_word for new trie");
    cr_assert_not_null(t->children['a']->children['n'] , "trie_add_node failed to allocate new entry");
    cr_assert_eq(t->children['a']->children['n']->is_word,1, "trie_insert_string failed to set is_word for end character");

    cr_assert_eq(t->children['a']->children['n']->is_word,1, "trie_insert_string failed to set is_word for end character");
    cr_assert_eq(t->children['a']->children['n']->children['t']->children['i']->is_word,1, "trie_insert_string failed to set is_word for end character");

    cr_assert_eq(t->children['a']->children['n']->children['t']->is_word,0, "trie_insert_string failed to set is_word for middle character");
    cr_assert_eq(t->children['a']->children['n']->children['t']->children['s']->is_word,1, "trie_insert_string failed to set is_word for end character");
}
