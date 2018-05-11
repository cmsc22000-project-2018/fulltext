Program Description

Goal: Implement a full-text search tool for text files with interactive user navigation of the file.

Operation Modes:

Interactive Mode: User must be able to open a text file, specify word(s) to be searched, and interactively navigate the file by skipping from matched word to next/previous matched word.

Batch Mode: Program must take a text file plus word(s) to be searched via command line arguments and produce the amount of occurences of the provided word(s) to either standard output or to a new file. It must also find all lines containing the specified word(s) and return those lines plus a configurable amount of lines before or after the found lines with the specified word(s).

We will be implementing the full-text search feature using a prefix trie by implementing the Aho-Corasick algorithm. The search pattern will be implemented with regular expression (regex).

For an in-depth explanation of Aho-Corasick, visit https://www.geeksforgeeks.org/aho-corasick-algorithm-pattern-searching/. For more information on regex, visit https://docs.microsoft.com/en-us/dotnet/standard/base-types/regular-expression-language-quick-reference.

Implementation

Classes Match File Trie IO Search

Match Purpose: A class for operations related to matches.

match struct:

char* word int line match* next match* prev

Operations for match:

match* new_match(char* word, int line) void init_match(match* match, char* word, int line) void free_match(match* match) char* get_word(match* match) int get_line(match* match)

Linked list operations on match:

match* next_match(match* match) match* prev_match(match* match) void insert_at(match* match, match* new, int index) void append(match* match, match* new) void remove_at(match* match, int index) match* get_at_index(match* match, int index) int get_index(match* match)

Notes:

Last match should point to first match as next match to include wrap-around functionality (and first match should point to last match as previous match).

File

file struct:

char *name char *content

Operations for file:

void open_file() file* parse_file()

Purpose: A class for operations related to the text file.

Database for the lines Read file Process the text file into seperate lines

Trie

trie struct

char current // The first node_t will be '/0' trie_t *children[ALPHABET_SIZE] int EOW; // if EOW is 1, reached end of a word ALPHABET_SIZE= 256;

Purpose: A class for the trie data structure and trie related operations. Implemented from Trie team.

Trie struct Trie operations

Input/Output

input struct:

char **command // array of strings

Operations for input:

void parse_input(char** commands)

sample commands:

list of options -b // batch mode -i // interactive mode (ie. fulltext -b [list of search words]) -l (number of lines) // specifies the number of lines before & after the searched word

commands fulltext // starts the program n // jumps to next matched word in interactive mode p // jumps to previous matched word in interactive mode Purpose: A class for interactive user input and output to stdout or another file.

Search Purpose: The core class for full-text program.