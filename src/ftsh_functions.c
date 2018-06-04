#include "ftsh.h"
#include "ftsh_functions.h"
#include "search.h"
#include "match.h"
#include "trie.h"
#include "../src/simclist.h"

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

    return 1;
}


int ftsh_exit(char **args, FILE *pf) {
    return 0;
}

int ftsh_find(char **args, FILE *pf) {
    int STATUS = 1;
    char buf[100];
    char *input;

    int start_line = 1;
    int BUFFER_LENGTH = 100;

    char *w1 = "knowledge";
    char *w2 = "ourselves";
    char *w3 = "from";
    char *strarr[4];
    strarr[0] = strdup(w1);
    strarr[1] = strdup(w2);
    strarr[2] = strdup(w3);
    strarr[3] = NULL;
    
    trie_t *trie = trie_new('\0');
    int ret = trie_from_stringarray(trie, strarr);
    assert (ret != EXIT_FAILURE);

    match curMatch;
    list_t matches;
    list_init(&matches);


    /* Finding first match at minimum */
    while (list_size(&matches) == 0 /*&& fgetc(pf) != EOF*/ ) {
        matches = *parse_file_buffered_trie(pf, start_line, \
                (start_line + BUFFER_LENGTH), trie, &matches);

        start_line += BUFFER_LENGTH;

        if (list_size(&matches) == 0) {
            printf("No matches for %s have been found.\n", "TESTWORD");
            return 1;
        }
    }

    int index = 0;
    curMatch = *match_get_at_index(index, &matches);

    list_info(&matches);

    match_display(stdout, &curMatch);

    while (STATUS) {
        printf("ftsh> ");
        input = fgets(buf, 5, stdin);

        // exit ./ftsh
        if (!input || strncmp(input, "exit", 5) == 0) exit(1);

        // exit find()
        if (strncmp(input, "quit", 5) == 0) STATUS = 0;

        // next/prev match
        if (strncmp(input, "next", 5) == 0) {

            display_next_match(&matches, index);
            index = (index+1)%list_size(&matches);

        } else if (strncmp(input, "prev", 5) == 0) {

            display_prev_match(&matches, index);
            index = (index-1+list_size(&matches))/list_size(&matches);

        }
    }

    return 1;

}

int ftsh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}


int ftsh_execute(char **args, FILE *pf) {
    int i;

    if (args[0] == NULL) {
        // An empty command was entered.
        return 1;
    }

    for (i = 0; i < ftsh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args, pf);
        }
    }

    return 0;
}
