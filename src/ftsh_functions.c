#include <stdlib.h>
#include <time.h>
#include "ftsh.h"
#include "ftsh_functions.h"
#include "search.h"
#include "match.h"
#include "trie.h"
#include "../src/simclist.h"


/*
    Defined variables for greater readability
 */
#define SHOULD_CONTINUE 1
#define SHOULD_EXIT 0

/*
    List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
    "help",
    "exit",
    "find"
};


int (*builtin_func[]) (char **, FILE *pf) = {
    &ftsh_help,
    &ftsh_exit,
    &ftsh_find
};


int ftsh_help(char **args, FILE *pf) {
    printf("\n Full text search program \n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    int i = 0;
    for (i = 0; i < ftsh_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    printf("When running find, you can iterate through the results using 'next' and 'prev'.\n");

    return SHOULD_CONTINUE;
}


int ftsh_exit(char **args, FILE *pf) {
    return SHOULD_EXIT;
}

int ftsh_find(char **args, FILE *pf) {
    int STATUS = SHOULD_CONTINUE;
    char buf[10];
    char *input;

    int start_line = 1;
    int BUFFER_LENGTH = 100;

    time_t current_time;
    char* c_time_string;

    // Error handling
    if (args[1] == '\0') {
        perror("No search words specified.\n");
        exit(1);
    }

    // Config trie

    current_time = time(NULL);
    c_time_string = ctime(&current_time);

    trie_t* words = trie_new(c_time_string);
    int i = 1;

    while (args[i] != '\0') {
        trie_insert(words, args[i]);
        i++;
    }

    match curMatch;
    list_t matches;
    list_init(&matches);

    // Reset to head of file if EOF had been reached
    if (feof(pf)) {
        fseek(pf, 0, SEEK_SET);
    }

    while (list_size(&matches) == 0 ) {
        matches = *parse_file_buffered(pf, start_line, \
                                       (start_line + BUFFER_LENGTH), words, &matches);

        start_line += BUFFER_LENGTH;

        if (list_size(&matches) == 0) {
            printf("No matches have been found.\n");
            return SHOULD_EXIT;
        }
    }

    int index = 0;
    curMatch = *match_get_at_index(index, &matches);

    list_info(&matches);

    match_display(&curMatch);

    while (STATUS) {
        printf("ftsh> ");
        input = fgets(buf, 6, stdin);

        // exit ./ftsh
        if (!input || strncmp(input, "exit\n", 5) == 0) {
            trie_free(words);
            exit(SHOULD_EXIT);
        }

        // exit find()
        else if (strncmp(input, "quit\n", 5) == 0) {
            STATUS = 0;
        }

        // Rerun find
        else if (strncmp(input, "find\n", 5) == 0) {
            printf("Please `quit` first before you run `find` again. \n");
            STATUS = 0;
        }

        // next/prev match
        else if (strncmp(input, "next\n", 5) == 0) {

            display_next_match(&matches, index);
            index = (index + 1) % list_size(&matches);

        } else if (strncmp(input, "prev\n", 5) == 0) {

            display_prev_match(&matches, index);
            index = ((index - 1) + list_size(&matches)) % list_size(&matches);

        }

        // exit find()
        else {
            trie_free(words);
            return SHOULD_CONTINUE;
        }
    }

    trie_free(words);
    return SHOULD_CONTINUE;
}

int ftsh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}


int ftsh_execute(char **args, FILE *pf) {
    int i;

    if (args[0] == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < ftsh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args, pf);
        }
    }

    return EXIT_SUCCESS;
}
