/***************************************************************************//**

	@file         ftsh.c

	@author       Max Bronckers

	@date         Thursday,  1 May 2018

	@brief        FTSH (Full-Text SHell)

	@compile      gcc -g -Wall -lreadline ftsh_functions.c ftsh.c -o ftsh

*******************************************************************************/

#include "ftsh.h"
#include "ftsh_functions.h"

/**
	@brief Parse input into args.
	@param input The input.
	@return Null-terminated array of args.
 */
char** ftsh_get_input(char *input) {
	char **args = malloc(8 * sizeof(char *));
	char *separator = " ";
	char *parsed;
	int index = 0;

	/* Error handling */
	if (args == NULL) {
			perror("malloc failed");
			exit(1);
	}

	parsed = strtok(input, separator);

	while (parsed != NULL) {
			args[index++] = parsed;
			parsed = strtok(NULL, separator); 
	}

	args[index] = NULL;
	return args;
}

/**
	@brief Launch a program and wait for it to terminate.
	@param args Null terminated list of arguments (including program).
	@return Always returns 1, to continue execution.
 */
int ftsh_launch(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0) {
		// Child process
		if (execvp(args[0], args) == -1) {
			printf("Your command was not recognized by our system. ");
			printf("Please type 'help' to get an overview of the commands.\n");
			perror("ftsh: command execution error");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		// Error forking
		perror("ftsh: forking error");
	} else {
		// Parent process
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

/**
	 @brief Loop getting input and executing it.
 */
void ftsh_loop(void)
{
	char *input;
	char **args;
	int status;

	do {
		input = readline("ftsh> ");
		args = ftsh_get_input(input);
		status = ftsh_execute(args);

		free(input);
		free(args);
	} while (status);
}

/**
	 @brief Main entry point.
	 @param argc Argument count.
	 @param argv Argument vector.
	 @return status code
 */
int main(int argc, char **argv)
{
	// Load config files, if any.

	// Run command loop.
	ftsh_loop();

	// Perform any shutdown/cleanup.

	return EXIT_SUCCESS;
}
