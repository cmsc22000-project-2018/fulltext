#ifndef _FULLTEXT_FTSH_FUNCTIONS_H_
#define _FULLTEXT_FTSH_FUNCTIONS_H_

/***************************************************************************//**

    @file         ftsh_functions.h

    @author       Max Bronckers

    @date         15 May 2018

    @brief        FTSH supported commandss

*******************************************************************************/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
    @brief Builtin command: print help.
    @param args List of args.  Not examined.
    @return Always returns 1, to continue executing.
 */
int ftsh_help(char **args, FILE *pf);


/**
    @brief Builtin command: exit.
    @param args List of args.  Not examined.
    @return Always returns 0, to terminate execution.
 */
int ftsh_exit(char **args, FILE *pf);


/**
    @brief Builtin command: find
           Finds the matched words in the loaded file.
    @param args List of args.
    @param pf Pointer to text file.
    @return Always return 1, to continue execution.
  */
int ftsh_find(char **args, FILE *pf);


/**
    @brief Number of built-in functions.
    @return Returns number of functions.
 */
int ftsh_num_builtins();


/**
     @brief Execute shell built-in or launch program.
     @param args Null terminated list of arguments.
     @param pf Pointer to text file
     @return 1 if the shell should continue running, 0 if it should terminate
 */
int ftsh_execute(char **args, FILE *pf);

#endif
