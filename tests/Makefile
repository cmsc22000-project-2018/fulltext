# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc 
CFLAGS = -fPIC -Wall -O2 -g -I../include/
LDFLAGS = -L../ -Wl,-rpath,../
RM = rm -f
BIN = test-mtrie
LDLIBS = -lcriterion -lmtrie

SRCS = main.c test_mtrie.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${BIN}

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN) $(LDLIBS) 

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d) $(BIN)


