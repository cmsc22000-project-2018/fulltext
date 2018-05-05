#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAXWORDNUM 100000
#define MAXWORDLEN 100
#define LINE_MAX 2048

char* SEP = " \t\n";

char* token = NULL;
char buffer[LINE_MAX];
FILE *ptr_file = fopen("my.txt","r");

void next_token()
{
    if (token != NULL) {
        token = strtok(NULL, SEP);
    }
    
    while (token == NULL) {
        // leave room so that we can insert extra space before the newline
        char* s = fgets(buffer, LINE_MAX, ptr_file);
        if (s == NULL) {
            if (ferror(stdin)) {
                fprintf(stderr, "Error reading input\n");
                exit(1);
            }
            assert(feof(stdin));
            break;
        }
        
        token = strtok(s, SEP);
    }
}

int read_string(char** s)
{
    *s = token;
    return token != NULL;
}

void init_parser()
{
    next_token();
}

char **parse_txt(void)
{
	init_parser();
	char **stringArray;
    stringArray = malloc(sizeof(char*)*MAXWORDNUM);
    assert(stringArray != NULL);

    char *s = NULL;
    while (int i = 0; i < MAXWORDNUM; i++) {
        if (!read_string(&s)) return NULL;
    	printf("%s\n", s);
    	stringArray[i] = s;
    	next_token();	
    }
    return NULL;
}

int main()
{
    // FILE *ptr_file;
    // ptr_file =fopen("my.txt","r");
    if (!ptr_file)
    	return 1;

    char **stringArray;
    stringArray = parse_txt();

    fclose(ptr_file);
    return 0;
}