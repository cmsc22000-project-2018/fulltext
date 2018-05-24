#include "ftsh.h"
#include "ftsh_functions.h"
#include "search.h"

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


int ftsh_help(char **args, FILE *pf)
{
    printf("...full-text search...\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    int i = 0;
    for (i = 0; i < ftsh_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    return 1;
}


int ftsh_exit(char **args, FILE *pf)
{
    return 0;
}


int ftsh_find(char **args, FILE *pf)
{
    /*int STATUS = 1;
    char buf[100];
    char *input;

    char * line = NULL;
    size_t len = 0;
    ssize_t read;*/
    
    char *word = args[1]; // word to search for
    //int wordlen = strlen(word);

    parse_file_buffered(pf, 1, 5, word);

    // search like 100 lines ?

    // print 1st match from linked list using display_match()

    // while (STATUS) {
    //     printf("ftsh> ");
    //     input = fgets(buf, 100, stdin);
        
    //     // exit find()
    //     if (!input) return 1;
        
    //     // next match
    //     if (strncmp(buf, "next", 4) == 0) {
            
    //         // if there is next match in linked list, print

    //         // if not, parse for 100 lines more, print out first match

    //         // if end of file is reached, print file searched. and print first match

    //     } else if (strncmp(buf, "prev", 4) == 0) {

    //         // print previous match in ll

    //     }


    //  }

    /* FIRST TRY TO GET ALL RESULTS */
    // Christina's function/code
    /*int found = -1;
    while ((read = getline(&line, &len, pf)) != -1) {
        char sanitized[strlen(line) + 1];
        strcpy(sanitized, line);
        
        sanitized[strcspn(sanitized, "\r\n")] = 0;

        char line2[strlen(sanitized)+1];
        strcpy(line2, sanitized);
        found = find_match(sanitized, word, 1, 1);
            
        while (found != -1 && found + wordlen < read) {
            char again[strlen(sanitized)+1-found + wordlen];
            strncpy(again, line2+found+wordlen, strlen(line2)-found-wordlen);
            memset(sanitized, ' ', found + wordlen);
            found = find_match(sanitized, word, found + wordlen+1, 1);
        }
    }*/

    return 1;

}

int ftsh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}


int ftsh_execute(char **args, FILE *pf)
{
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
