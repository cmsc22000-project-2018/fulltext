# Makefile based on template at https://gist.github.com/xuhdev/1873316
# Makefile partially based on CMSC 220 Lab 3 and Lab 5

CC = gcc 
CFLAGS = -fPIC -Wall -std=gnu99 -O2 -g -I../include/ -I../src/ -I../api/include/ 
LDFLAGS = -L../tests/ -Wl,-rpath=./tests/ -L../api/ -Wl,-rpath=./api/ 
RM = rm -f
BIN = test-fulltext
LDLIBS = -lcriterion -lfulltext -lreadline -lredisApi

# Add your test file below in SRCS
SRCS = main.c test_ftsh.c test_match.c test_parser.c
OBJS = $(SRCS:.c=.o)

# Add the src/c files that your test files depend on below in LIB_SRCS
LIB_SRCS = ../src/ftsh.c ../src/ftsh_functions.c ../src/match.c ../src/search.c ../src/parser.c

LIB_OBJS = $(LIB_SRCS:.c=.o)
LIB_BIN = libfulltext.so

.PHONY: all

all: $(BIN)

# Makes the main binary test-fulltext
$(BIN): $(LIB_BIN) $(OBJS) 
		$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

#Makes the object files for the libraries for testing purposes
$(TARGET_LIB): $(OBJS)
		$(CC) $(LDFLAGS) -o $@ $^

# Makes the libraries for testing purposes
$(LIB_BIN): $(LIB_OBJS)
		$(CC) -shared $^ -o $@

# Deletes all .o, .so, and bin files
.PHONY: clean
clean:
	-${RM} $(LIB_BIN) $(LIB_OBJS) ${OBJS} $(BIN)
