#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include "match.h"
#include "simclist.h"
#include "search.h"

// Helper for checking whether two matches equal
// in word, lineNum, position and line
void match_equal(match result, match expected)
{
    //printf("Expected line \"%s\" but got \"%s\"\n", result.line, expected.line);
    cr_assert_str_eq(result.word, expected.word, 
    	"Expected word %s but got %s", result.word, expected.word);
    cr_assert_eq(result.lineNum, result.lineNum,
    	"Expected line %d but got %d", result.lineNum, result.lineNum);
    cr_assert_eq(result.position, result.position,
    	"Expected position %d but got %d", result.position, result.position);
    cr_assert_str_eq(result.line, expected.line,
    	"Expected line \"%s\" but got \"%s\"", result.line, expected.line);
}

/* Testing find_match() function */
// lineNum is set as 1 in all following tests
// Checks if the pos returned from find_match() is correct
void check_find_match_pos(char* line, char* word, int pos_start, list_t* matches, int expected)
{
	int lineNum = 1;
	int result = find_match(line, word, pos_start, lineNum, matches);
	cr_assert_eq(result, expected,
		"expected pos to be %d but find_match() returns %d",
		expected, result);
}

// Checks if the append to list is correctly performed if pos != -1
void check_find_match_matches(char* line, char* word, int pos_start, list_t* matches, int index)
{

	int lineNum = 1;
	int result = find_match(line, word, pos_start, lineNum, matches);
        //printf("list size: %d\n", list_size(&matches));
	if (result != -1) {
		match expectedMatch;
		expectedMatch.word = word;
		expectedMatch.lineNum = lineNum;
		expectedMatch.position = result;
		expectedMatch.line = line;
		match *foundMatch = match_get_at_index(index, matches);
		cr_assert_not_null(foundMatch, "match wasn't found at pos %d", result);
		cr_assert_not_null(matches, "match found but could not append");
		match_equal(expectedMatch, *foundMatch);
	}
}

// Case where there is a single match in line
Test(search, find_one_existent_match)
{
        char *line1 = "Scepticism is as much the result of knowledge, as knowledge is of";
	char *word1 = "result";
	list_t matches1;
	list_init(&matches1);
	check_find_match_pos(line1, word1, 0, &matches1, 26);
	check_find_match_matches(line1, word1, 0, &matches1, 0);
}

// Case where the first word in line is a match
Test(search, find_one_existent_match_first)
{
	char *line3 = "ourselves from, knowledge previously acquired; we must set aside old";
	char *word3 = "ourselves";
	list_t matches3;
	list_init(&matches3);
	check_find_match_pos(line3, word3, 0, &matches3, 0);
	check_find_match_matches(line3, word3, 0, &matches3, 0);
}

// Case where the last word in line is a match
Test(search, find_one_existent_match_last)
{
	char *line2 = "ourselves from, knowledge previously acquired; we must set aside old";
	char *word2 = "old";
	list_t matches2;
	list_init(&matches2);
	check_find_match_pos(line2, word2, 0, &matches2, 64);
	check_find_match_matches(line2, word2, 0, &matches2, 0);
}

// Cases where there are two matches in line
Test(search, find_two_existent_matches)
{
	char line1[66] = "Scepticism is as much the result of knowledge, as knowledge is of";
        char line1copy[66];
        strncpy(line1copy, line1, 66);
        
	char *word1 = "knowledge";
	list_t matches1;
	list_init(&matches1);
	check_find_match_pos(line1, word1, 0, &matches1, 36);
	check_find_match_matches(line1, word1, 0, &matches1, 0);
        memset(line1, ' ', 46);
	check_find_match_pos(line1, word1, 47, &matches1, 50);
	check_find_match_matches(line1copy, word1, 47, &matches1, 1);
}

// Cases where there are two matches in line, first and last word
Test(search, find_two_existent_matches_first_last)
{
	char line1[52] = "is as much the result of knowledge, as knowledge is";
        char line1copy[52];
        strncpy(line1copy, line1, 52);

	char *word1 = "is";
	list_t matches1;
	list_init(&matches1);
	check_find_match_pos(line1, word1, 0, &matches1, 0);
	check_find_match_matches(line1, word1, 0, &matches1, 0);
        memset(line1, ' ', 3);
	check_find_match_pos(line1, word1, 4, &matches1, 49);
	check_find_match_matches(line1copy, word1, 4, &matches1, 1);
}

// Cases where there are mtultiple matches in line
Test(search, find_mult_existent_matches)
{
	char line1[41] = "pretty cats are pretty pretty and pretty";
        char* line1copy = "pretty cats are pretty pretty and pretty";

        char *word1 = "pretty";
	list_t matches1;
	list_init(&matches1);
	check_find_match_pos(line1, word1, 0, &matches1, 0);
	check_find_match_matches(line1copy, word1, 0, &matches1, 0);
        memset(line1, ' ', 7);
	check_find_match_pos(line1, word1, 7, &matches1, 16);
	check_find_match_matches(line1copy, word1, 8, &matches1, 1);
        memset(line1, ' ', 17);
	check_find_match_pos(line1, word1, 17, &matches1, 23);
	//check_find_match_matches(line1copy, word1, 25, &matches1, 2);
        memset(line1, ' ', 25);
	check_find_match_pos(line1, word1, 24, &matches1, 33);
	check_find_match_matches(line1copy, word1, 32, &matches1, 3);
}

// Cases where there is no match in line
Test(search, find_nonexistent_match)
{
	char *line1 = "Scepticism is as much the result of knowledge, as knowledge is of Scepticism.";
	char *word1 = "skepticism";
	list_t matches1;
	list_init(&matches1);
	check_find_match_pos(line1, word1, 0, &matches1, -1);

	char *line2 = "unlearning something which it has cost us no small labour and anxiety to";
	char *word2 = "its";
	list_t matches2;
	list_init(&matches2);
	check_find_match_pos(line2, word2, 0, &matches2, -1);
}

/* Testing parse_file_buffered() function */
Test(search, parse_file_buffered)
{

}
