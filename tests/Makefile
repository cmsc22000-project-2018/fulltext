# .RECIPEPREFIX +=
# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc 
CFLAGS = -fPIC -Wall -O2 -g -I../include/ `pkg-config --cflags --libs glib-2.0`
LDFLAGS = -L../ -Wl,-rpath,../ `pkg-config --libs glib-2.0`
RM = rm -f
BIN = test-fulltext
LDLIBS = -lcriterion -lmtrie -lmatch -lglib-2.0

SRCS = main.c test_mtrie.c test_match.c
OBJS = $(SRCS:.c=.o)

LIB_SRCS = ../src/ftsh.c
LIB_OBJS = ../src/ftsh.o

.PHONY: lib

$(LIB_OBJS): $(LIB_SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

lib: $(LIB_OBJS)
	$(CC) -shared $< -o libftsh
	

.PHONY: all
all: ${BIN}

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o$(BIN) $(LDLIBS) 

$(SRCS:.c=.d): %.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d) $(BIN)
