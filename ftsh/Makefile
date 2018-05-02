CC = gcc

CFLAGS = -g -lreadline -Wall

SRCS = ftsh.c ftsh_functions.c

OBJS = $(SRCS:.c=.o)

BINS = ftsh

RM = rm -f

.PHONY: ftsh
ftsh:
	$(CC) $(CFLAGS) $(SRCS) -o $(BINS)  

.PHONY: clean
clean:
	-$(RM) $(OBJS) $(BINS)
