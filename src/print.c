#include <stdio.h>
#include <stdlib.h>
#include "match.h"
#include "simclist.h"
#include "simclist.c"

void print_colors(char *word, match *google) 
{
	int size = 5;
	printf("%d\n", size);
	printf("\033[1;31m");
	printf("%s\n", word);
	printf("\033[0m");
}

int main()
{
	char *word = "boogie";
	match *yahoo = NULL;
	print_colors(word, yahoo);
	return 0;
}
