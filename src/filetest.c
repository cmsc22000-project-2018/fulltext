#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int main(int argc, char *argv[]) 
{
	FILE *fp = fopen("tests/filetest.txt", "r");
	int line_num = 0;
	int pos = 0;

	char buf[6];
	char *line = NULL;
	char *token, *save_ptr;

	size_t len = 0;
	ssize_t read;

	while ((read = getline(&line, &len, fp)) != -1) {
		line_num++;
		printf("\non line %d:\n", line_num);

		token = strtok_r(line, " ,.!?\t\n", &save_ptr);
		while (token != NULL) {
			if ((fgets(buf, 6, stdin) != NULL)
				&& (strncmp(buf, "next", 4) == 0)) {
				pos++;
				printf("\tpos %d  %s\n", pos, token);
				token = strtok_r(NULL, " ,.!?\t\n", &save_ptr);			
			}
		}

		pos = 0;
	}
	return 0;
}
