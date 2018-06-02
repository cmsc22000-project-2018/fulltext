#include <stdbool.h>
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

void ftsh_loop(FILE *pf, bool interactive) {
    char *input;
    char **args;
    int status;

    if (!interactive) {
        printf("To be implemented.\n");
        return;
    }

    do {
        input = readline("ftsh> ");
        args = ftsh_get_input(input);
        status = ftsh_execute(args, pf);

        free(input);
        free(args);
    } while (status);
}

int main(int argc, char **argv) {
    // Validating the correct number of parameters
    if (argc <= 1) {
        printf("Usage: ./ftsh <text_search_file>\n");
        printf("Add option '-b' to start batch mode\n");
        exit(0);
    }

    // if interactive = false, then batch mode
    bool interactive = true;
    // Tracker to path argument position
    int path_num = 1;

    // Checking whether batch mode 
    if (argc == 3) {
        if (!strncmp(argv[1], "-b", 2)) {
            printf("Batch mode detected\n");
            path_num = 2;
            interactive = false;
        } else if (!strncmp(argv[2], "-b", 2)) {
            printf("Batch mode detected\n");
            path_num = 1;
            interactive = false;
        } else {
            perror("Wrong command line options");
            exit(1);
        }
    }

    char *path = (argv[path_num] != NULL) ? argv[path_num] : NULL;
    FILE *pf = fopen(path, "r");

    if (pf == NULL) {
        perror("Search file could not be opened");
        exit(1);
    }

//<<<<<<< HEAD
    ftsh_loop(pf, interactive);
/*
=======
    if (argc == 4) {
        if (!strncmp(argv[2], "-b", 2)) {
            mode = 0;
            char *batchpath = argv[3];
            pb = fopen(batchpath, "r");
            if (pb == NULL) {
            	perror("Batch file could not be opened");
            	exit(1);
            }
            char **search_terms_arr = parse_to_arr(pb);
            trie_t *t = trie_new('\0');
            int ret = trie_from_stringarray(t, search_terms_arr);
            assert (ret != EXIT_FAILURE); // trie created successfully

            list_t matches;
            list_init(&matches);
            matches = *find_matches_batch(pf, t, &matches);
            display_matches_batch(&matches);
>>>>>>> f7f33d53de1b1794283aa0415e03b63213cc31a2
*/

    // Clean up
    fclose(pf);

    return EXIT_SUCCESS;
/*    
        @ Ruolin!
        I commented out this code because I think this belongs in search
        once the program is running. Refactor it to however you see fit.
        */
}
