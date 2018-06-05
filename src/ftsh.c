#include "ftsh.h"
#include "ftsh_functions.h"
#include "search.h"


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


void ftsh_loop(FILE *pf) {
    char *input;
    char **args;
    int status;

    do {
        input = readline("ftsh> ");
        args = ftsh_get_input(input);
        status = ftsh_execute(args, pf);

        free(input);
        free(args);
    } while (status);
}


char* get_path(int argc, char **argv) {
    if (argc <= 1) {
        return NULL;
    }

    return (argv[1] != NULL) ? argv[1] : NULL;
}

int main(int argc, char **argv) {

    // Config
    char* path = get_path(argc, argv);
    if (argc == 1 || path == NULL) {
        printf("Usage: ./ftsh <text_search_file>\n");
        exit(0);
    }
    FILE *pf = fopen(path, "r");
    int mode = 1;

    if (pf == NULL) {
        perror("File could not be opened");
        exit(1);
    }

    // Interactive mode
    if (mode == 1) {
        ftsh_loop(pf);
    }

    // Batch mode
    if (!mode) {
        printf("To be implemented.\n");
    }

    // Clean up
    fclose(pf);

    return EXIT_SUCCESS;
}
