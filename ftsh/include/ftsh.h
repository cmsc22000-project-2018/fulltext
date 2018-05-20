#ifndef FTSH
#define FTSH

/***************************************************************************//**

	@file         ftsh_functions.h

	@author       Max Bronckers

<<<<<<< HEAD
	@date         Thursday,  1 May 2018
=======
	@date         Thursday, 1 May 2018
>>>>>>> 209c5a7c9b97c43e1bd2deb901289f52aded7d2f

	@brief        FTSH main header file

*******************************************************************************/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
<<<<<<< HEAD
// #include <readline/readline.h>
=======
#include <readline/readline.h>
>>>>>>> 209c5a7c9b97c43e1bd2deb901289f52aded7d2f

char** ftsh_get_input(char *input);

int ftsh_launch(char **args);

void ftsh_loop(void);

int main(int argc, char **argv);

#endif