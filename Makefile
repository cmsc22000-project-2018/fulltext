CC = gcc
SRCS = src/ftsh.c src/ftsh_functions.c
OBJS = $(SRCS:.c=.o)
BINS = ftsh
LDLIBS = -lreadline
RM = rm -rf
LIB = libmtrie.so
CFLAGS = -g -O2 -Wall -I ./include/ -I ./src/ -fPIC
MT_SRCS = src/mtrie.c
MT_OBJS = src/mtrie.o

all: $(LIB) ftsh

.PHONY: $(LIB)

$(LIB): $(MT_OBJS)
	$(CC) -shared $(MT_OBJS) -o $(LIB)

$(MT_OBJS): $(MT_SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: ftsh
ftsh:
	$(CC) $(CFLAGS) $(SRCS) -o $(BINS) $(LDLIBS)

.PHONY: clean
clean:
	-$(RM) $(OBJS) $(BINS) $(MT_OBJS) $(LIB)
