#include "ftsh.h"
#include "ftsh_functions.h"

stringArray *pf = NULL;

/*
 * List of builtin commands, followed by their corresponding functions.
 */

char *builtin_str[] = {
    "help",
    "exit",
    "load"
};


int (*builtin_func[]) (char **) = {
    &ftsh_help,
    &ftsh_exit,
    &ftsh_load
};


int ftsh_help(char **args)
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


int ftsh_exit(char **args)
{
    return 0;
}


int ftsh_load(char **args)
{
    char ch;
    char *path = args[1]; // second argument is filepath
    
    FILE *fp = fopen(path, "r");

    if (fp == NULL) {
        perror("File could not be opened");
        exit(1);
    }
 
<<<<<<< 9f1043a626b751b6b7984c90dde11efdc6ca4f53
    // fclose(fp);
=======
	pf = parse_to_arr(fp);

   	fclose(fp);
>>>>>>> Initial linkage of parser and shell

    return 1;
}


int ftsh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}


int ftsh_execute(char **args)
{
    int i;

    if (args[0] == NULL) {
        // An empty command was entered.
        return 1;
    }

    for (i = 0; i < ftsh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return ftsh_launch(args);
}
