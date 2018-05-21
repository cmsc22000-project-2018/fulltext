# .RECIPEPREFIX +=
# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc 
CFLAGS = -fPIC -Wall -O2 -g -I../include/ #'pkg-config --cflags --libs glib-2.0'#
LDFLAGS = -L../tests/ -Wl,-rpath=../tests/ #'pkg-config --libs glib-2.0'#
RM = rm -f
BIN = test-fulltext
LDLIBS = -lcriterion -lfulltext -lglib-2.0 -lreadline

SRCS = main.c test_ftsh.c
OBJS = $(SRCS:.c=.o)

TEST_SRCS = test_ftsh.c test_match.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

LIB_SRCS = ../src/ftsh.c ../src/ftsh_functions.c ../src/match.c
LIB_OBJS = $(LIB_SRCS:.c=.o)
LIB_BIN = libfulltext.so

.PHONY: all
all: $(BIN)

# Makes the main binary test-fulltext
$(BIN): $(LIB_BIN) $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

# Makes the object files for the libraries for testing purposes
$(LIB_OBJS): $(LIB_SRCS)
	$(CC) $(CFLAGS) -c $^ -o $@

# Makes the libraries for testing purposes
$(LIB_BIN): $(LIB_OBJS)
	$(CC) -shared $^ -o $@

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

# Makes the object files for the testing functions
#test_objs: 
#	$(CC) $(CFLAGS) -c -o $(TEST_OBJS) $(TEST_SRCS) $(LDLIBS)

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d) $(BIN)
