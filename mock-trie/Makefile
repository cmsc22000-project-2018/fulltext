CC = gcc
CFLAGS = -g -O2 -Wall -Wextra -I ./include
SRCS = src/mtrie.c
OBJS = src/mtrie.o
BIN = mtrie

$(BIN): $(SRCS)
	$(CC) $^ $(CFLAGS) -o $@

$(OBJS): mtrie.h

clean:
	$(RM) $(OBJS) $(BIN)
