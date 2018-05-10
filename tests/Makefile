.RECIPEPREFIX +=
CC = gcc 
CFLAGS = -Wall -Wextra -O2 -g -I../include/ -fPIC `pkg-config --cflags --libs glib-2.0`
LDFLAGS = -L../ -Wl,-rpath,../ `pkg-config --libs glib-2.0`
RM = rm -f
BIN = test-match
LDLIBS = -lcriterion -lmatch -lglib-2.0

SRCS = main.c match_test.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: $(BIN)

$(BIN): $(OBJS)
  $(CC) $(LDFLAGS) $(OBJS) -o $(BIN) $(LDLIBS) 

$(TARGET_LIB): $(OBJS)
  $(CC) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
  $(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
  -${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d) $(BIN)