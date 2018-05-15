#ifndef _FULLTEXT_FTSH_FUNCTIONS_H
#define _FULLTEXT_FTSH_FUNCTIONS_H

/***************************************************************************//**

    @file         ftsh_functions.h

    @author       Max Bronckers

    @date         15 May 2018

    @brief        Text search operations

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ftsh.h"
#include "ftsh_functions.h"

/**
    @brief Stub function for searching a parsed file for words
    @param word_set Set of words to search for
    @param pf Parsed text file to search through
    @return (Stub: void) a linked list of matches
 */
void search(char** word_set, stringArray* pf);



#endif
