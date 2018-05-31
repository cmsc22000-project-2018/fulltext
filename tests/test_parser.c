#include <stdlib.h>
#include <stdio.h>

#include "parser.h"
#include "trie.h"

void test_parser()
{
	printf(" ----- INSERTING ----- \n");
	char* s1 = "apples";
	char* s2 = "bananas";
	trie_t* new_trie = trie_new("test");

	char **strarray = malloc(3*sizeof(char*));
	strarray[0] = s1;
	strarray[1] = s2;
	strarray[2] = NULL;

	int r = trie_from_stringarray(new_trie, strarray);
	
	int contain1 = trie_contains(new_trie, "apples"); // 0
	int contain2 = trie_contains(new_trie, "bananas"); // 0
	int uncontain = trie_contains(new_trie, "carrots"); // 1
	int prefix = trie_contains(new_trie, "app"); // 2

	printf(" ----- KEY ----- \n");
	printf("0 - word is contained in trie \n");
	printf("1 - word is not contained in trie \n");
	printf("2 - word is a prefix in the trie \n");
	printf("\n");

	printf("TRIE_CONTAINS(apples): %d\n", contain1);
	printf("TRIE_CONTAINS(bananas): %d\n", contain2);
	printf("TRIE_CONTAINS(carrots): %d\n", uncontain);
	printf("TRIE_CONTAINS(app): %d\n", prefix);
	
	trie_free(new_trie);
}
