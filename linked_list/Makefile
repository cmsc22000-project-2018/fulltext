.RECIPEPREFIX +=
CC = gcc

CFLAGS = -O2 -Wall -Wextra -g -I ./include/ -fPIC -c `pkg-config --cflags --libs glib-2.0`
LDLIBS = `pkg-config --libs glib-2.0`

SRCS = src/match.c

OBJS = $(SRCS:.c=.o)

BINS = src/match.o

RM = rm -rf

LIB = libmatch.so

all: match
  $(CC) -shared -o $(LIB) $(OBJS)

match:
  $(CC) $(SRCS) $(CFLAGS) -o $(BINS) $(LDLIBS)

.PHONY: clean
clean:
  -${RM} ${LIB} ${OBJS} $(BIN)
  make -C ./tests clean

tests: ${TARGET_LIB}
  make -C ./tests