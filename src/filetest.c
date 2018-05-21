#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

// This is a simple mimic of the file flow
// following ftsh_load(), read_until_next_match(), print_match()

void print_match(char *line, char *word, int line_num, int pos, long int filepos)
{
	printf("word: %s\nline %d pos %d fp %lu:\n%s\n", 
		word, line_num, pos, filepos, line);
}

// returns 0 when EOF
int read_until_next_match(FILE *fp, char *word, int line_num)
{
    char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	int pos = 0;
	long int filepos = 0;
	char *token, *saveptr, *saveln;

    while ((read = getline(&line, &len, fp)) != -1) {
    	pos = 0;
    	saveln = strdup(line);
    	token = strtok_r(line, " ,.!?\t\n", &saveptr);
		while (token != NULL) {
			pos++;
			if (strncmp(word, token, strlen(word)) == 0) {
				filepos = ftell(fp);
				print_match(saveln, word, line_num, pos, filepos);
				return 1;
			}
			token = strtok_r(NULL, " ,.!?\t\n", &saveptr);			
		}
		free(saveln);
	}
	return 0;
}

int main(int argc, char *argv[]) 
{
    char buf[100];
    char *pinput;

	int save_line_num = 0;
	int ret = -1;

	if (argc != 2) {
		printf("usage: ./filetest <search_term>\n");
		exit(0);
	}
	
    char *word = argv[1];

    FILE *fp = fopen("tests/filetest.txt", "r");

    while (1) {
        printf("fulltext> ");
        pinput = fgets(buf, 100, stdin);
        
        if (!pinput) {
            exit(0);
        }
       
        if (strncmp(buf, "next", 4) == 0) {
        	save_line_num++;
      	    ret = read_until_next_match(fp, word, save_line_num);
            if (ret == 0) {
        	    printf("Reach EOF.\n");
        	    exit(0);
            }
         }
     }

	return 0;	
}
