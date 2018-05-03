#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mtrie.h"
// #include "match.h"

void check_is_key_in_trie(trie_t *unused, const char *key, bool expected)
{
	trie_t t;
	bool result = is_key_in_trie(&t, key);
	cr_assert_eq(result, expected, 
		"%s is %s trie but got %s",
                key,
		result ? "in " : "not in ",
		expected ? "in" : "not in");
}

Test(trie, key_in_trie)
{
	trie_t unused;
	check_is_key_in_trie(&unused, "a", 1);
	check_is_key_in_trie(&unused, "an", 1);
	check_is_key_in_trie(&unused, "and", 1);
	check_is_key_in_trie(&unused, "at", 1);
	check_is_key_in_trie(&unused, "b", 1);
	check_is_key_in_trie(&unused, "be", 1);
}

Test(trie, not_key_in_trie)
{
	trie_t unused;
	check_is_key_in_trie(&unused, "ant", 0);
	check_is_key_in_trie(&unused, "bee", 0);
	check_is_key_in_trie(&unused, "o", 0);
	check_is_key_in_trie(&unused, "of", 0);
	check_is_key_in_trie(&unused, "off", 0);
	check_is_key_in_trie(&unused, "z", 0);
}

Test(trie, insert)
{

}

Test(trie, num_matches)
{

}

Test(trie, return_matches_m)
{

}
