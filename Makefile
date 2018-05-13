# .RECIPEPREFIX +=
CC = gcc
SRCS = src/ftsh.c src/ftsh_functions.c src/parser.c
OBJS = $(SRCS:.c=.o)
FTSH_BIN = ftsh
LDLIBS = -lreadline `pkg-config --libs glib-2.0`
RM = rm -rf
LIB = libmtrie.so
CFLAGS = -g -O2 -Wall -std=c99 -I ./include/ -I ./src/ -fPIC `pkg-config --cflags --libs glib-2.0`
MT_SRCS = src/mtrie.c
MT_OBJS = src/mtrie.o

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
	$(CC) $(MATCH_SRCS) $(CFLAGS) -c -o $(MATCH_BINS) $(LDLIBS)

.PHONY: $(MATCH_LIB)
$(MATCH_LIB): match
	$(CC) -shared -o $(MATCH_LIB) $(MATCH_OBJS)

.PHONY: ftsh
ftsh: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(FTSH_BIN) $(LDLIBS)

.PHONY: clean 
clean:
	$(RM) $(OBJS) $(FTSH_BIN) $(MT_OBJS) $(LIB) $(MATCH_OBJS) $(MATCH_LIB)
	make -C ./tests clean

tests: $(OBJS)
	make -C ./tests
