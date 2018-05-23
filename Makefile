# .RECIPEPREFIX +=
CC = gcc
SRCS = src/ftsh.c src/ftsh_functions.c src/search.c
OBJS = $(SRCS:.c=.o)
FTSH_BIN = ftsh
LDLIBS = -lreadline
RM = rm -rf

LIB = libtrie.so
CFLAGS = -g -O2 -Wall -Wextra -I ./include/ -I ./src/ -fPIC `pkg-config --cflags --libs glib-2.0`

MT_SRCS = src/trie.c
MT_OBJS = src/trie.o

MATCH_SRCS = src/match.c
MATCH_OBJS = $(MATCH_SRCS:.c=.o)
MATCH_BINS = src/match.o
MATCH_LIB = libmatch.so


all: $(LIB) $(FTSH_BIN) $(MATCH_LIB)

.PHONY: $(LIB)
$(LIB): $(MT_OBJS)
	$(CC) -shared $(MT_OBJS) -o $(LIB)

$(MT_OBJS): $(MT_SRCS)
	$(CC) $(CFLAGS) -c $< -o $@
 
.PHONY: match
match:
	$(CC) $(CFLAGS) $(MATCH_SRCS) -c -o $(MATCH_BINS) 

.PHONY: $(MATCH_LIB)
$(MATCH_LIB): match
	$(CC) -shared -o $(MATCH_LIB) $(MATCH_OBJS)

.PHONY: ftsh
ftsh: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(FTSH_BIN) $(LDLIBS)

# this is a hard-coded rule and should never be made by 'all'
# this is neither removed by 'clean'
.PHONY: filetest
filetest: ./src/filetest.c
	$(CC) $(CFLAGS) ./src/filetest.c -o filetest

.PHONY: clean 
clean:
	$(RM) $(OBJS) $(FTSH_BIN) $(MT_OBJS) $(LIB) $(MATCH_OBJS) $(MATCH_LIB)
	make -C ./tests clean

tests: $(OBJS)
	make -C ./tests

