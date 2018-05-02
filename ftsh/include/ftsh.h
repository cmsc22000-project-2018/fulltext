#ifndef FTSH
#define FTSH

/***************************************************************************//**

	@file         ftsh_functions.h

	@author       Max Bronckers

	@date         Thursday, 1 May 2018

	@brief        FTSH main header file

*******************************************************************************/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>

char** ftsh_get_input(char *input);

int ftsh_launch(char **args);

void ftsh_loop(void);

int main(int argc, char **argv);

#endif