# Product Documentation 

FTSH is full-text search tool with Redis support for text files. It supports interactive and batch mode, with syntax highlighting, user navigation, and an efficient search algorithm.

### Usage:

Interactive Mode: 
- Use -i flag to start interactive mode.
- Specify the textfile path in command line while starting the program:

  ```
  ./ftsh -i PATH/FILE
  ```
- Run `find word1 word2 ... wordN` to start looking for words:

  ```
  ftsh> find word1
  ```
- Iterate through found words in text with `next` and `prev`:

  ```
  ftsh> next
  ftsh> prev
  ```

Batch Mode:
- Specify the textfile path using `-p` flag and the words to search with `-w` in command line to run the program:

  ```
  ./ftsh -p PATH/FILE -w word1 word2
  ```
 
 
# System Documentation

Program must take a text file plus word(s) to be searched via command line arguments and produce the amount of occurences of the provided word(s) to either standard output or to a new file. It must also find all lines containing the specified word(s) and return those lines plus a configurable amount of lines before or after the found lines with the specified word(s).

We will be implementing the full-text search feature using a prefix trie by implementing the Aho-Corasick algorithm. The search pattern will be implemented with regular expression (regex).

For an in-depth explanation of Aho-Corasick, visit https://www.geeksforgeeks.org/aho-corasick-algorithm-pattern-searching/. For more information on regex, visit https://docs.microsoft.com/en-us/dotnet/standard/base-types/regular-expression-language-quick-reference.

# Implementation

## Classes: Match, FTSH, Trie, Search

### Match

Purpose: A class for operations related to matches.

match struct:

- char* word 
- int line
- match* next
- match* prev

Operations:

match* new_match(char* word, int line)
void init_match(match* match, char* word, int line)
void free_match(match* match)
char* get_word(match* match)
int get_line(match* match)

Linked list operations on match:

- match* next_match(match* match)
- match* prev_match(match* match)
- void insert_at(match* match, match* new, int index)
- void append(match* match, match* new)
- void remove_at(match* match, int index)
- match* get_at_index(match* match, int index)
- int get_index(match* match)

Notes:

Last match should point to first match as next match to include wrap-around functionality (and first match should point to last match as previous match).



### Input/Output

input struct:

char **command // array of strings

Operations for input:

void parse_input(char** commands)

sample commands:

list of options -b // batch mode -i // interactive mode (ie. fulltext -b [list of search words]) -l (number of lines) // specifies the number of lines before & after the searched word

commands fulltext // starts the program n // jumps to next matched word in interactive mode p // jumps to previous matched word in interactive mode Purpose: A class for interactive user input and output to stdout or another file.

### Search

Purpose: The core class for full-text program.


