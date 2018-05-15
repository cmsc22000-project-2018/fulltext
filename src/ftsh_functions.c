/***************************************************************************//**

	@file         ftsh_functions.c

	@author       Max Bronckers

	@date         Thursday, 1 May 2018

	@brief        FTSH functions

*******************************************************************************/

#include "ftsh.h"
#include "ftsh_functions.h"
#include "parser.h"
#include "string.h"

/*
 * Global variable for parsed file in stringArray struct
 */
stringArray *pf = NULL;

/*
	List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
	"help",
	"exit",
	"load",
    "find"
};

int (*builtin_func[]) (char **) = {
	&ftsh_help,
	&ftsh_exit,
	&ftsh_load,
    &ftsh_find
};

/**
	@brief Builtin command: print help.
	@param args List of args.  Not examined.
	@return Always returns 1, to continue executing.
 */
int ftsh_help(char **args)
{
	printf("Full-Text Shell:\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");

	for (int i = 0; i < ftsh_num_builtins(); i++) {
		printf("  %s\n", builtin_str[i]);
	}

	printf("Use the man command for information on other programs.\n");
	return 1;
}

/**
	@brief runs search for provided words in args on loaded file
	@param args List of words to search for in file
	@return Return 1 in case of succesfull execution.
 */
int ftsh_find(char **args) 
{
	int SET_SIZE = 0;
	char** word_set = malloc(8 * sizeof(char *));

    for (int i = 0; args[i] != NULL; i++) {
        word_set[i] = strdup(args[i]);
        SET_SIZE++;
    }

    word_set[SET_SIZE] = NULL; // mark end of word set

	return 1;
}

/**
	@brief Builtin command: exit.
	@param args List of args.  Not examined.
	@return Always returns 0, to terminate execution.
 */
int ftsh_exit(char **args)
{
	return 0;
}

/**
	@brief Builtin command: load [filepath]
	@param args List of args. [filepath]
	@return Always returns 1, to continue execution.
	@credit: https://www.programmingsimplified.com/c-program-read-file
 */
int ftsh_load(char **args)
{
	char ch;
	char *path = args[1]; // second argument is filepath
	
	FILE *fp = fopen(path, "r");

	if (fp == NULL) {
		perror("File could not be opened");
		exit(1);
	}
 
	pf = parse_to_arr(fp);

   	fclose(fp);

   	return 1;
}

/**
	@brief Number of built-in functions.
	@return Returns number of functions.
 */
int ftsh_num_builtins() {
	return sizeof(builtin_str) / sizeof(char *);
}

/**
	 @brief Execute shell built-in or launch program.
	 @param args Null terminated list of arguments.
	 @return 1 if the shell should continue running, 0 if it should terminate
 */
int ftsh_execute(char **args)
{
	int i;

	if (args[0] == NULL) {
		// An empty command was entered.
		return 1;
	}

	for (i = 0; i < ftsh_num_builtins(); i++) {
		if (strcmp(args[0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(args);
		}
	}

	return ftsh_launch(args);
}
