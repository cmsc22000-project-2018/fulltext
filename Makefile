.RECIPEPREFIX +=
CC = gcc
SRCS = src/ftsh.c src/ftsh_functions.c
OBJS = $(SRCS:.c=.o)
FTSH_BIN = ftsh
LDLIBS = -lreadline
RM = rm -rf
LIB = libmtrie.so
CFLAGS = -g -O2 -Wall -std=c99 -I ./include/ -I ./src/ -fPIC 
MT_SRCS = src/mtrie.c
MT_OBJS = src/mtrie.o

MATCH_SRCS = src/match.c
MATCH_OBJS = $(MATCH_SRCS:.c=.o)
MATCH_BINS = src/match.o
MATCH_LIB = libmatch.so

PRINT_SRCS = src/print.c
PRINT_OBJS = $(PRINT_SRCS:.c=.o)
PRINT_BINS = print
PRINT_LIBS = -lmatch
DYN_LDFLAGS = -L../fulltext -Wl,-rpath,../fulltext

all: $(LIB) $(FTSH_BIN) $(MATCH_LIB) print

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

.PHONY: print
print: $(PRINT_BINS)

src/print.c:
  $(CC) $(CFLAGS) src/print.c -o print

src/print.o: src/print.c

print: src/print.o
  $(CC) $(DYN_LDFLAGS) $^ -o $@ $(PRINT_LIBS)

.PHONY: ftsh
ftsh: $(SRCS)
  $(CC) $(CFLAGS) $(SRCS) -o $(FTSH_BIN) $(LDLIBS)

.PHONY: clean 
clean:
  $(RM) $(OBJS) $(FTSH_BIN) $(MT_OBJS) $(LIB) $(MATCH_OBJS) $(MATCH_LIB) $(PRINT_BINS)
  make -C ./tests clean

tests: $(OBJS)
  make -C ./tests
