#include "ftsh.h"
#include "ftsh_functions.h"


char** ftsh_get_input(char *input) {
    char **args = malloc(8 * sizeof(char *));
    char *separator = " ";
    char *parsed;
    int index = 0;

    /* Error handling */
    if (args == NULL) {
        perror("ftsh malloc failed");
        exit(1);
    }

    /* Exit on Ctrl-D */
    if (input == NULL) {  
        printf("\n");
        exit(0);
    }

    parsed = strtok(input, separator);

    while (parsed != NULL) {
        args[index++] = parsed;
        parsed = strtok(NULL, separator); 
    }

    args[index] = NULL;
    return args;
}


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


int main(int argc, char **argv)
{
    ftsh_loop();

    return EXIT_SUCCESS;
}
