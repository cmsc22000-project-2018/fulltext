CC = gcc

CFLAGS = -g -lreadline -Wall -O3 -I ./include/

SRCS = src/ftsh.c src/ftsh_functions.c

OBJS = $(SRCS:.c=.o)

BINS = ftsh

DSYM = *.dSYM

RM = rm -rf

.PHONY: ftsh
ftsh:
	$(CC) $(CFLAGS) $(SRCS) -o $(BINS)  

.PHONY: clean
clean:
	-$(RM) $(OBJS) $(BINS) $(DSYM)
