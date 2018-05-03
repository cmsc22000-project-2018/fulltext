#cc dll_test.c `pkg-config --cflags --libs glib-2.0` -o dll_test

CC = gcc

CFLAGS = `pkg-config --cflags --libs glib-2.0` -g -Wall -O3 
#LDLIBS = `pkg-config --libs glib-2.0`

SRCS = src/dll_test.c

OBJS = $(SRCS:.c=.o)

BINS = src/dll_test

RM = rm -rf

.PHONY: dll
dll:
	$(CC) $(SRCS) $(CFLAGS) -o $(BINS)  

.PHONY: clean
clean:
	-$(RM) $(OBJS) $(BINS) $(DSYM)
