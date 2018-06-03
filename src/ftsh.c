#include <stdbool.h>
#include <unistd.h>
#include "ftsh.h"
#include "ftsh_functions.h"
#include "search.h"
#include "parser.h"
#include "trie.h"


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

char **ftsh_get_words(char **args) {
    char **words = malloc(8 * sizeof(char *));
    int i = 1; // 0 = `find`
    while (args[i] != '\0') {
        words[i] = args[i];
        i++;
    }
    words[i] = NULL;
    return words;
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

int main(int argc, char *argv[]) {
    // Default mode = batch
    bool interactive = false;
    int opt;
    char *path = NULL;
    char *words = NULL;
    // if no batch output specified, output to stdout
    char *output = "stdout";
    FILE *searchfile = NULL;

    const char *usage = "Usage: ./ftsh [-ib] <batch_output_file> -f <text_search_file> -w <words>\n";

    // Validating the correct number of parameters
    if (argc <= 1) {
        printf("%s", usage);
        exit(1);
    }

    while ((opt = getopt(argc, argv, "ib::f:w:")) != -1)
        switch (opt) {
            case 'i': 
                interactive = true;
                break;
            case 'b':
                interactive = false;
                if (optarg != NULL) {
                    output = strdup(optarg);
                }
                break;
            case 'f':
                path = strdup(optarg);
                searchfile = fopen(path, "r");
                if (searchfile == NULL) {
                    printf("ERROR: Search file could not be opened");
                    exit(1);
                }
                break;
            case 'w':
                words = strdup(optarg);
                break;
            default:
                printf("Unknown option -%c", opt);
                exit(1);
        }

    if (path == NULL || searchfile == NULL) {
        printf("ERROR: No search file entered\n");
        printf("%s", usage);
        exit(1);
    }
    
    if (words == NULL) {
        printf("ERROR: No search words entered\n");
        printf("%s", usage);
        exit(1);
    }

    if (interactive) {
        ftsh_loop(searchfile);
    } else {
        // Testing batch
        printf("Batch mode detected\n");
        printf("Output: %s\n", output);
        printf("Search file: %s\n", path);
        printf("Word(s): %s\n", words);
    }

    /* Commented out for now until batch output is considered
    search_batch(searchfile, batchfile);
    */

    // Clean up
    fclose(searchfile);

    return EXIT_SUCCESS;
}
