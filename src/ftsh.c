#include "ftsh.h"
#include "ftsh_functions.h"
#include "search.h"
#include "parser.h"


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
        printf("Usage: ./ftsh <text_search_file> {-i | -b <text_search_terms>}\n");
        exit(0);
    }
    FILE *pf = fopen(path, "r");
    FILE *pb = NULL;
    // 1 for interactive and 0 for batch
    int mode = 1;

    if (pf == NULL) {
        perror("Search file could not be opened");
        exit(1);
    }

    if (argc == 4) {
        if (!strncmp(argv[2], "-b", 2)) {
            mode = 0;
            char *batchpath = argv[3];
            pb = fopen(batchpath, "r");
            if (pb == NULL) {
            	perror("Batch file could be opened");
            	exit(1);
            }
            char **search_terms_arr = parse_to_arr(pb);
            for (int i = 0; search_terms_arr[i] != NULL; i++)
            	printf("%s\n", search_terms_arr[i]);
        }
        // Returning from Batch mode
        if (pb) fclose(pb);
        exit(0);
    }

    ftsh_loop(pf);

    // Interactive mode
    if (mode == 1) {
        ftsh_loop(pf);
    }

    // Clean up
    fclose(pf);

    return EXIT_SUCCESS;
}
