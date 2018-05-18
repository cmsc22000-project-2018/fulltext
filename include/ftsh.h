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
#include <sys/types.h>

/**
    @brief Parse input into args.
    @param input The input.
    @return Null-terminated array of args.
 */
char** ftsh_get_input(char *input);


/**
    @brief Launch a program and wait for it to terminate.
    @param args Null terminated list of arguments (including program).
    @return Always returns 1, to continue execution.
 */
int ftsh_launch(char **args);


/**
     @brief Loop getting input and executing it.
 */
void ftsh_loop(void);


/**
     @brief Main entry point.
     @param argc Argument count.
     @param argv Argument vector.
     @return status code
 */
int main(int argc, char **argv);

#endif
