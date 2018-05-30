#ifndef _FULLTEXT_FTSH_H_
#define _FULLTEXT_FTSH_H_

/***************************************************************************//**

	@file         ftsh_functions.h

	@author       Max Bronckers

	@date         15 May 2018

	@brief        FullText SHell main file

*******************************************************************************/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>

/**
    @brief Parse input into args.
    @param input The input.
    @return Null-terminated array of args.
 */
char** ftsh_get_input(char *input);


char **ftsh_get_words(char **args);

/**
     @brief Loop getting input and executing it.
     @args pf Pointer to text file.
 */
void ftsh_loop(FILE *pf);


/**
    @brief Takes arguments and returns the file path from the args.
    @param argc Argument count.
    @param argv Argument vector.
    @return pointer to file path
  */
char* get_path(int argc, char **argv);
/**
     @brief Main entry point.
     @param argc Argument count.
     @param argv Argument vector.
     @return status code
 */
int main(int argc, char **argv);

#endif
