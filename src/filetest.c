#include "filetest.h"
#include "match.h"

int find_match(char* line, char* word, int pos_start, int lineNum)
{
    if (strlen(word) > strlen(line)) return -1;
    char* line2 = line;
    int pos = pos_start;
    char* token = strtok_r(line2, " ,.!?\r\t\n", &line2);
    while (token != NULL) {
        if (strcmp(token, word) == 0) {
            printf("match found: %s at pos %d line %d\n", token, pos, lineNum);
            return pos;
        }
        pos += strlen(token) + 1;
        token = strtok_r(NULL, " ,.!?\r\t\n", &line2);
    }
    return -1;
}

void parse_file_buffered(FILE* fp, int start_line, int end_line, char* word)
{
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int wordlen = strlen(word);

    int found = -1;
    int lineNum = start_line;
    while (lineNum <= end_line && (read = getline(&line, &len, fp)) != -1) {
        printf("---------------------");
        printf("\nline %d: %s", lineNum, line);

        char sanitized[strlen(line)+1];
        strcpy(sanitized, line);
        sanitized[strcspn(sanitized, "\r\n")] = 0;

        char line2[strlen(sanitized)+1];
        strcpy(line2, sanitized);
        found = find_match(sanitized, word, 1, lineNum);
        while (found != -1 && found + wordlen < read) {
            memset(sanitized, ' ', found + wordlen);
            found = find_match(sanitized, word, found + wordlen + 1, lineNum);
        }
        lineNum++;
        printf("---------------------\n");
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: ./filetest <search_term>\n");
        exit(0);
    }

    FILE* fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    char *word = argv[1];
    printf("print from lines 1 to 3\n");
    parse_file_buffered(fp, 1, 3, word);
    printf("print from lines 4 to 7\n");
    parse_file_buffered(fp, 4, 7, word);

    fclose(fp);
    //if (line)
    //    free(line);
    exit(EXIT_SUCCESS);
}

/*// This is a simple mimic of the file flow
// following ftsh_load(), read_until_next_match(), print_match()

void print_match(char *line, char *word, int line_num, int pos, long int filepos)
{
	printf("word: %s\nline %d pos %d fp %lu:\n%s\n", 
		word, line_num, pos, filepos, line);
}

// returns number of occurrences in line
int num_occurrences(char *line, char *word)
{
    char *token, *saveptr;
    int count = 0;
    token = strtok_r(line, " ,.!?\t\n", &saveptr);
    while (token != NULL) {
        count++;
        token = strtok_r(NULL, " ,.!?\t\n", &saveptr);
    }
    return count;
}

// returns 0 when EOF
int read_until_next_match(FILE *fp, char *word, int line_num)
{
    char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	int pos = 0;
	long int filepos = 0;
	char *token, *saveptr, *saveln, *saveln2;

    while ((read = getline(&line, &len, fp)) != -1) {
    	pos = 0;
    	saveln = strdup(line);
    	saveln2 = strdup(line);
    	// very inefficient way to check for multiple occurrences
    	int num_occ = num_occurrences(saveln2, word);
    	token = strtok_r(line, " ,.!?\t\n", &saveptr);
		while (token != NULL) {
			pos++;
			if (strncmp(word, token, strlen(word)) == 0) {
				filepos = ftell(fp);
				print_match(saveln, word, line_num, pos, filepos);
				return num_occ-1;
			}
			token = strtok_r(NULL, " ,.!?\t\n", &saveptr);			
		}
		free(saveln);
		free(saveln2);
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
    FILE *save_fp = fdopen(dup(fileno(fp)), "r");

    while (1) {
        printf("fulltext> ");
        pinput = fgets(buf, 100, stdin);
        
        if (!pinput) {
            exit(0);
        }
       
        if (strncmp(buf, "next", 4) == 0) {
        	if (ret != 0) {
        		save_line_num++;
      	    	ret = read_until_next_match(fp, word, save_line_num);
      	    	while (ret > 0) {
      	    		ret = read_until_next_match(save_fp, word, save_line_num);
      	    	}
      	    	save_fp = fp;
      	    }
            else {
        	    printf("Reached.\n");
        	    exit(0);
            }
         }
     }

    return 0;	
}*/



