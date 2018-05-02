#ifndef FTSH_FUNCTIONS
#define FTSH_FUNCTIONS

/***************************************************************************//**

	@file         ftsh_functions.h

	@author       Max Bronckers

	@date         Thursday, 1 May 2018

	@brief        FTSH supported commands header file

*******************************************************************************/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int ftsh_help(char **args);

int ftsh_exit(char **args);

int ftsh_num_builtins();

int ftsh_execute(char **args);

#endif