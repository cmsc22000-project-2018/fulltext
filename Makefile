LIB = libmtrie.so
CC = gcc
CFLAGS = -g -O2 -Wall -Wextra -I ./include/ -I ./src/ -fPIC -c
RM = rm -f
SRCS = src/mtrie.c
OBJS = src/mtrie.o

all: $(LIB)

.PHONY: $(LIB)

$(LIB): $(OBJS)
	$(CC) -shared $(OBJS) -o $(LIB)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(LIB)
