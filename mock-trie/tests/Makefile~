C = gcc
CFLAGS = -g -O2 -Wall -Wextra -I ../include
SRCS = main.c test_mtrie.c
OBJS = $(SRCS:.c:.o)
BIN = mtrie-tests
RM = rm -rf
LDLIBS = -lcriterion
LDFLAGS = -L../ -Wl,-rpath,.

.PHONY: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(LDFLAGS) $^ $(CFLAGS) -o $@ $(LDLIBS)

.PHONY: clean
clean: 
	$(RM) $(OBJS) $(BIN)

