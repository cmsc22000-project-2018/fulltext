#ifndef INCLUDE_FILE_H_
#define INCLUDE_FILE_H_

/* File struct */
typedef struct {
    char* name;
    char* content;
} file;

/* Opens the file */
void open_file();

/* Parses the file */
file* parse_file();

#endif /* INCLUDE_FILE_H_ */
