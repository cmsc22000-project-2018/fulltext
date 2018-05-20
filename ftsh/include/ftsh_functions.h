#ifndef FTSH_FUNCTIONS
#define FTSH_FUNCTIONS

/***************************************************************************//**

	@file         ftsh_functions.h

	@author       Max Bronckers

<<<<<<< HEAD
	@date         Thursday,  1 May 2018
=======
	@date         Thursday, 1 May 2018
>>>>>>> 209c5a7c9b97c43e1bd2deb901289f52aded7d2f

	@brief        FTSH supported commands header file

*******************************************************************************/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

<<<<<<< HEAD
char *builtin_str[];

=======
>>>>>>> 209c5a7c9b97c43e1bd2deb901289f52aded7d2f
int ftsh_help(char **args);

int ftsh_exit(char **args);

int ftsh_num_builtins();

int ftsh_execute(char **args);

#endif