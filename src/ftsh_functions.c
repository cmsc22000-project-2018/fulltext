#include "ftsh.h"
#include "ftsh_functions.h"


/*
    List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
    "help",
    "exit",
    "next"
};


int (*builtin_func[]) (char **, FILE *pf) = {
    &ftsh_help,
    &ftsh_exit,
    &ftsh_next
};


int ftsh_help(char **args, FILE *pf)
{
    printf("Full-Text Shell:\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (int i = 0; i < ftsh_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}


int ftsh_exit(char **args, FILE *pf)
{
    return 0;
}


int ftsh_next(char **args, FILE *pf)
{
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
