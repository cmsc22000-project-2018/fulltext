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
    int STATUS = 1;
    char buf[100];
    char *pinput;

	int save_line_num = 0;
	int ret = -1;

    char *word = args[1]; // word to search for
    
    while (STATUS) {
        printf("ftsh> ");
        pinput = fgets(buf, 100, stdin);
        
        if (!pinput) {
            return 1;
        }
        
        // next match
        if (strncmp(buf, "next", 4) == 0) {
        	save_line_num++;
      	    ret = read_until_next_match(pf, word, save_line_num);
            if (ret == 0) {
        	    printf("Reach EOF.\n");
        	    return 1;
            }
         }
     }
    
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
