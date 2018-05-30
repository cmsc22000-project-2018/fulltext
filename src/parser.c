#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "parser.h"
#include "trie.h"

#define MAXWORDNUM 10000
#define MAXWORDLEN 100
#define LINE_MAX 2048

char* SEP = " \t\n";

char* token = NULL;
char buffer[LINE_MAX];

void next_token(FILE *fp) {
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

int read_string(char** s) {
    *s = token;
    return token != NULL;
}

void init_parser(FILE *fp) {
    next_token(fp);
}

char **parse_to_arr(FILE *fp) {
    init_parser(fp);
    char **strarr;
    strarr = malloc(sizeof(char*)*MAXWORDNUM);
    assert(strarr != NULL);

    char *s = NULL;
    for (int i = 0; i < MAXWORDNUM; i++) {
        strarr[i] = malloc(sizeof(char)*MAXWORDLEN);
        if (!read_string(&s)) {
            strarr[i] = NULL;
            break;
        }
        strncpy(strarr[i], s, sizeof(strarr[i]));
        next_token(fp);
    }

    assert(strarr != NULL);
    return strarr;
}

int trie_from_stringarray(char **strarr) {
    int ret = 0;
    trie_t* t = trie_new('\0');

    for (int i = 0; strarr[i] != NULL; i++) {
        ret = trie_insert(t, strarr[i]);
        if (ret == -1) return -1;
    }
    return 0;
}
