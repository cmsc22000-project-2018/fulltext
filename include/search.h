#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/**
  Header comments to be written by author of functions @Ruolin
  */
void print_match(char *line, char *word, int line_num, int pos, long int filepos);


/**
  Header comments to be written by author of functions @Ruolin
  */
int read_until_next_match(FILE *pf, char *word, int line_num);
