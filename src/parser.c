#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAXWORDNUM 100000
#define MAXWORDLEN 100

static const size_t LINE_MAX = 2048;
static const char* SEP = " \t\n";

static char* token = NULL;
static char buffer[LINE_MAX];

void init_parser()
{
    next_token();
}

void next_token()
{
    if (token != NULL) {
        token = strtok(NULL, SEP);
    }
    
    while (token == NULL) {
        // leave room so that we can insert extra space before the newline
        char* s = fgets(buffer, LINE_MAX, stdin);
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

char **parse_txt(void)
{
    char **buf;
    buf = malloc(sizeof(char[MAXWORDNUM][MAXWORDLEN]));
    assert(buf != NULL);
    char *s = NULL;
    if (!read_string(&s)) return NULL;
}

int main()
{
    FILE *ptr_file;
    ptr_file =fopen("my.txt","r");
  if (!ptr_file)
      return 1;
    
  parse_txt();

fclose(ptr_file);
return 0;
}