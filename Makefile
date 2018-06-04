CC = gcc

# Add any files that need to be compiled into the executable below in SRCS
SRCS = src/ftsh.c src/ftsh_functions.c src/search.c src/match.c src/parser.c src/simclist.c
OBJS = $(SRCS:.c=.o)
BIN = ftsh
CFLAGS = -g -O2 -Wall -std=gnu99 -I ./include/ -I ./src/ -I ./api/include/ -fPIC 
LDLIBS = -lreadline -lredisApi
RM = rm -rf

.PHONY: all
all: $(BIN)

$(BIN): $(OBJS)
	make -C ./api
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN) -L./api -Wl,-rpath,./api $(LDLIBS)

.PHONY: clean 
clean: 
	$(RM) $(OBJS) $(BIN)
	make -C ./tests clean
	make -C ./api clean

tests: $(OBJS)
	make -C ./tests
