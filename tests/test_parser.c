Test(parser, trie_from_stringarray) {
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
