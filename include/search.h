#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

void print_match(char *line, char *word, int line_num, int pos, long int filepos);

int read_until_next_match(FILE *pf, char *word, int line_num);
