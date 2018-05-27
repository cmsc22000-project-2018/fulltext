#include "filetest.h"
#include "match.h"

int find_match(char* line, char* word, int pos_start, int lineNum) {
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

void parse_file_buffered(FILE* fp, int start_line, int end_line, char* word) {
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

int main(int argc, char *argv[]) {
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
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}

