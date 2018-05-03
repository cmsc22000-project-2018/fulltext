CC = gcc
CFLAGS = -fPIC -g -O2 -Wall -Wextra -I ../include
RM = rm -rf
LDLIBS = -lcriterion
LDFLAGS = -L../ -Wl,-rpath,.
SRCS = main.c test_mtrie.c eyeball_test_mtrie.c
OBJS = $(SRCS:.c:.o)
BINS = mtrie-tests


.PHONY: all
all: $(BINS)

$(BINS): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean: 
	$(RM) $(OBJS) $(BIN)

