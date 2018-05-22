#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "print.h"
#include "match.h"

/* See print.h */
void red() {
    printf("\033[1;31m");
}

/* See print.h */
void def() {
    printf("\033[0m");
}

/* See print.h */
char **parse_line(char *line)
{
    /* Declaring parsed string array to pass to print_match */
    char **parsed = malloc(sizeof(line));
    const char s[2] = " ";

    /* Getting the first token */
    char *token = strtok(line, s);

    /* Iterating through the rest of the line */
    for (int i=0; token != NULL; i++) {
        parsed[i] = token;
        token = strtok(NULL, s);
    }
    
    return parsed;
}

/* See print.h */
void print_match(match *m_word, char *line)
{
	// Checking right input
    printf("Matched word: %s\n", m_word->word);
    printf("Associated line: %s\n", line);

    /* Retrieving a parsed string array of words for line */
    char ** parsed = parse_line(line);

    /* Retrieving matched word and word position from match struct */
    char *word = m_word->word;
    int pos = m_word->position;
    
    /* Printing the words in the associated line until the matched word */
    int i = 0;
    for ( ; i<pos; i++) {
        printf("%s ", parsed[i]);
    }

    /* Setting the highlight color, printing the matched word, and
       returning to the default color */
    red();
    printf("%s ", word);
    def();

    /* If the matched word is not the end of the associated line, prints
       the remaining words in the associated line */
    if (parsed[i+1] != NULL) {
        i++;
        for ( ; parsed[i] != NULL; i++) {
            printf("%s ", parsed[i]);
        }
    }
    printf("\n");
}

/* Testing function */
int main()
{
    // Defining a match struct for testing 1
    match *sample = malloc(sizeof(match));
    sample->word = "this";
    sample->line = 3;
    sample->position = 3;

	// Sample associated line with testing 1
    char sample_line[] = "Can you highlight this in the line";

    print_match(sample, sample_line);

    //Testing 2
    printf("\n \n");
    match *sample2 = malloc(sizeof(match));
    sample2->word = "How";
    sample2->line = 6;
    sample2->position = 0;

    char sample_line2[] = "How are you doing?";
    
    print_match(sample2, sample_line2);

    //Testing 3
    printf("\n \n");
    match *sample3 = malloc(sizeof(match));
    sample3->word = "world.";
    sample3->line = 2;
    sample3->position = 5;

    char sample_line3[] = "Robots will take over the world.";

    print_match(sample3, sample_line3);

	return 0;
}
