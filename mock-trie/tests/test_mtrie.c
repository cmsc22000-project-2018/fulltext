#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mtrie.h"
#include "match.h"

void check_is_key_in_trie(trie_t *unused, const char *key, bool expected)
{
	trie_t t;
	bool result = is_key_in_trie(&t, key)
	cr_assert_eq(result, expected, 
		"%s is "
		result ? "in " : "not in "
		"trie but got "
		expected ? "in" : "not in",
		key);
}

Test(trie, key_in_trie)
{
	trie_t unused;
	check_is_key_in_trie(&unused, "a");
	check_is_key_in_trie(&unused, "an");
	check_is_key_in_trie(&unused, "and");
	check_is_key_in_trie(&unused, "at");
	check_is_key_in_trie(&unused, "b");
	check_is_key_in_trie(&unused, "be");
}

Test(trie, not_key_in_trie)
{
	trie_t unused;
	check_is_key_in_trie(&unused, "ant");
	check_is_key_in_trie(&unused, "bee");
	check_is_key_in_trie(&unused, "o");
	check_is_key_in_trie(&unused, "of");
	check_is_key_in_trie(&unused, "off");
	check_is_key_in_trie(&unused, "z");
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