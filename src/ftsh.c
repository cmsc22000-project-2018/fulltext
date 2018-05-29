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
    if (argv[2] != NULL && argc >= 3) {
        return argv[2];
    }
    printf("Usage: ./ftsh [-ib] <text_search_file> <word1> <word2> ...\n");
    exit(0);

}

int main(int argc, char **argv) {

    // Config
    char* path;
    char* flags = "ib";
    int opt;
    int mode = -1;

    path = get_path(argc, argv);
    FILE *pf = fopen(path, "r");

    while ((opt = getopt(argc, argv, flags)) != -1) {
        switch (opt) {
        case 'i':
            mode = 1;
            break;
        case 'b':
            mode = 0;
            break;
        default:
            perror("Usage: ./ftsh [-ib] <text_search_file> [<word1> <word2>] ...\n");
            exit(1);
        }
    }

    // Error handling
    if (pf == NULL) {
        perror("File could not be opened");
        exit(1);
    } else if (mode == -1) {
        perror("Mode was not selected");
        exit(1);
    }
    
    // Interactive mode
    if (mode == 1) {
        ftsh_loop(pf);
    }

    // Batch mode
    if (mode == 0) {
        printf("To be implemented...\n");
    }

    // Clean up
    fclose(pf);

    return EXIT_SUCCESS;
}
