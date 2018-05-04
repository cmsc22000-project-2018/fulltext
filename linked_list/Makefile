CC = gcc

CFLAGS = `pkg-config --cflags --libs glib-2.0` -g -Wall -O3 -I ./include/
#LDLIBS = `pkg-config --libs glib-2.0`

SRCS = src/match.c tests/match_test.c #src/dll_test.c 

OBJS = $(SRCS:.c=.o)

BINS = match_test #src/dll_test 

RM = rm -rf

.PHONY: all
all:
	$(CC) $(SRCS) $(CFLAGS) -o $(BINS)  

#.PHONY: dll
#dll:
#	$(CC) $(SRCS) $(CFLAGS) -o $(BINS)  
 
#.PHONY: match
#match:
#	$(CC) $(SRCS) $(CFLAGS) -o $(BINS)  

.PHONY: clean
clean:
	-$(RM) $(OBJS) $(BINS)
