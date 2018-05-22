/* Created: May 20 2018
   Author(s): Liam Kim */

#ifndef _FULLTEXT_PRINT_H
#define _FULLTEXT_PRINT_H

#include "match.h"

/* This match struct is temporary. I created it for the purposes of 
   writing the print.c function because I couldn't link match to
   my c file for some reason. */
/*typedef struct {
    char *word;
    int line;
    int position;
} match_t;*/

/**
   @brief: Sets the print color to red (highlight color)
   @param: n/a
   @return: n/a
*/
void red();

/**
   @brief: Sets the print color to default
   @param: n/a
   @return: n/a
*/
void def();

/**
   @brief: Using strtok, parses the given associated line
           into a string array of words to be used in print_match
   @param: char *line [associated line]
   @return: char **parsed [string array of parsed words]
*/
char **parse_line(char *line);

/**
   @brief: Given a match, prints the associated line and highlights
          the matched word
   @param: match_t *m_word [matched word with its position and line number
             in a match struct]
           char *line [string associated with the line]
   @return: void because of print function
*/
void print_match(match *m_word, char *line);

#endif
