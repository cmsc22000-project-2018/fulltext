#include <stdlib.h>
#include "ftsh.h"
#include "ftsh_functions.h"
#include "search.h"
#include "match.h"
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
    printf("[FULL-TEXT SEARCH]\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    int i = 0;
    for (i = 0; i < ftsh_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    return SHOULD_EXIT;
}


int ftsh_exit(char **args, FILE *pf) {
    return SHOULD_EXIT;
}


int ftsh_find(char **args, FILE *pf) {
    int status = SHOULD_CONTINUE;
    char buf[100];
    char *input;

    int start_line = 1;
    int BUFFER_LENGTH = 100;
    char *word = args[1];

    match curMatch;
    list_t matches;
    list_init(&matches);


    /* Finding first match at minimum */
    while (list_size(&matches) == 0 && fgetc(pf) != EOF) {
        matches = *parse_file_buffered(pf, start_line, \
                                       (start_line + BUFFER_LENGTH), word, &matches);

        start_line += BUFFER_LENGTH;

        if (fgetc(pf) == EOF && list_size(&matches) == 0) {
            printf("No matches for %s have been found.\n", word);
            return SHOULD_EXIT;
        }
    }

    int index = 0;
    curMatch = *match_get_at_index(index, &matches);

    match_display(&curMatch);
    list_info(&matches);

    /* NEEDS FIX */
    while (status == SHOULD_CONTINUE) {
        printf("ftsh> ");
        input = fgets(buf, 5, stdin);

        // exit find()
        if (!input || strncmp(input, "exit", 5) == 0) exit(SHOULD_EXIT);

        // next match
        if (strncmp(input, "next", 5) == 0) {
            display_next_match(&matches, index);
            index = (index+1)%list_size(&matches);

        } else if (strncmp(input, "prev", 5) == 0) {

            display_prev_match(&matches, index);
            index = (index-1+list_size(&matches))/list_size(&matches);

        }

    }

    return SHOULD_EXIT;

}

int ftsh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}


int ftsh_execute(char **args, FILE *pf) {
    int i;

    if (args[0] == NULL) {
        // An empty command was entered.
        return EXIT_FAILURE;
    }

    for (i = 0; i < ftsh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args, pf);
        }
    }

    return EXIT_SUCCESS;
}
