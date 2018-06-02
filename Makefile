CC = gcc

# Add any files that need to be compiled into the executable below in SRCS
SRCS = src/ftsh.c src/ftsh_functions.c src/search.c src/match.c src/simclist.c
OBJS = $(SRCS:.c=.o)
BIN = ftsh
CFLAGS = -g -O2 -Wall -std=gnu99 -I ./include/ -I ./src/ -fPIC 
LDLIBS = -lreadline 
RM = rm -rf

.PHONY: all
all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

.PHONY: clean 
clean: 
	$(RM) $(OBJS) $(BIN)
	make -C ./tests clean

tests: $(OBJS)
	make -C ./tests
