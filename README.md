# Program Description

Goal: Implement a full-text search tool for text files with interactive user navigation of the file.

# Operation Modes:

Interactive Mode: User must be able to open a text file, specify word(s) to be searched, and interactively navigate the file by skipping from matched word to next/previous matched word.

Batch Mode: Program must take a text file plus word(s) to be searched via command line arguments and produce the amount of occurences of the provided word(s) to either standard output or to a new file. It must also find all lines containing the specified word(s) and return those lines plus a configurable amount of lines before or after the found lines with the specified word(s).

# Implementation

## Installing

To use our program, first run the following command:

git clone https://github.com/cmsc22000-project-2018/fulltext.git

Make sure all submodules are also added: it may be necessary to run the following if the api submodule is empty after pulling:

git rm -f api/

git submodule add https://github.com/cmsc22000-project-2018/api.git

cd api/lib/

git rm -f redis-tries/

git submodule add https://github.com/cmsc22000-project-2018/redis-tries.git

Then, from the root project directory, run make

## Interactive Mode

Type the following from the root of the fulltext directory to open interactive mode:

./ftsh [text-search-file]

This will open the Fulltext search shell, from which the following commands can be run:

## Batch Mode

Type the following from the root of the fulltext directory to run batch mode:

./ftsh [-ib] [batch-output-file] -f [text-search-file] -w [words]
