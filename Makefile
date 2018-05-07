CC = gcc

CFLAGS = -g -Wall -O3 -I ./include/

SRCS = src/ftsh.c src/ftsh_functions.c

OBJS = $(SRCS:.c=.o)

BINS = ftsh

LDLIBS = -lreadline

RM = rm -rf

.PHONY: ftsh
ftsh:
	$(CC) $(CFLAGS) $(SRCS) -o $(BINS) $(LDLIBS)

.PHONY: clean
clean:
	-$(RM) $(OBJS) $(BINS)