CC = gcc
CFLAGS = -g -O2 -Wall -Wextra

mtrie: mtrie.c
	$(CC) $^ $(CFLAGS) -o $@

mtrie.o: mtrie.h

clean:
	$(RM) mtrie.o mtrie
