#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "parser.h"

#define MAXWORDNUM 10000
#define MAXWORDLEN 100
#define LINE_MAX 2048

char* SEP = " \t\n";

char* token = NULL;
char buffer[LINE_MAX];

void next_token(FILE *fp)
{
    if (token != NULL) {
        token = strtok(NULL, SEP);
    }
    
    while (token == NULL) {
        // leave room so that we can insert extra space before the newline
        char* s = fgets(buffer, LINE_MAX, fp);
        if (s == NULL) {
            if (ferror(fp)) {
                fprintf(stderr, "Error reading input\n");
                exit(1);
            }
            assert(feof(fp));
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

void init_parser(FILE *fp)
{
    next_token(fp);
}

char **parse_to_arr(FILE *fp)
{
	init_parser(fp);
	char **strarr;
	strarray = malloc(sizeof(char*)*MAXWORDNUM);
    	assert(strarr != NULL);

    	char *s = NULL;
    	for (int i = 0; i < MAXWORDNUM; i++) {
            strarray[i] = malloc(sizeof(char)*MAXWORDLEN);
            if (!read_string(&s)) {
		strarray[i] = NULL;
		break;	
            } 
    	    strncpy(strarray[i], s, sizeof(strarray[i]));
    	    next_token(fp);	
    }

    assert(strarr != NULL);
    return strarr;
}
