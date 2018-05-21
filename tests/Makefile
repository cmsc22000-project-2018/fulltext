# .RECIPEPREFIX +=
# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc 
CFLAGS = -fPIC -Wall -O2 -g -I../include/
LDFLAGS = -L../tests/ -Wl,-rpath=../tests/
RM = rm -f
BIN = test-fulltext
LDLIBS = -lcriterion -lmtrie -lmatch -lglib-2.0

SRCS = main.c test_ftsh.c
OBJS = $(SRCS:.c=.o)

LIB_SRCS = ../src/ftsh.c ../src/ftsh_functions.c
LIB_OBJS = ../src/ftsh.o ../src/ftsh_functions.o
LIB_BIN = test-fulltext-lib

.PHONY: lib

$(LIB_OBJS): $(LIB_SRCS)
	$(CC) $(CFLAGS) -c $^ -o $@

lib: $(LIB_OBJS)
	$(CC) -shared $^ -o libftsh.so

lib_test: ftsh lib
	$(CC) $(LDFLAGS) $(OBJS) -o $(LIB_BIN) -lftsh -lcriterion -lreadline

ftsh:
	$(CC) -O2 -Wall -Wextra -g -fPIC -I ./include/ -c -o test_ftsh.o test_ftsh.c
	

.PHONY: all
all: ${BIN}

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o$(BIN) $(LDLIBS) 

$(SRCS:.c=.d): %.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d) $(BIN)
