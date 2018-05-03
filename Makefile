LIB = libmtrie.so
CC = gcc
CFLAGS = -g -O2 -Wall -Wextra -I ./include -I ./src -fPIC -c
RM = rm -f
SRCS = src/mtrie.c
OBJS = $(SRCS:.c:.o)

all: $(LIB)

.PHONY: $(BIN)

$(LIB): $(OBJS)
	$(CC) -shared -o $(LIB) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BIN)
