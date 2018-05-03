CC = gcc
CFLAGS = -g -O2 -Wall -Wextra -I ./include
SRCS = src/mtrie.c
OBJS = $(SRCS:.c:.o)
BIN = mtrie
RM = rm -rf

.PHONY: $(BIN)

$(BIN): $(SRCS)
	$(CC) $^ $(CFLAGS) -o $@

clean:
	$(RM) $(OBJS) $(BIN)
