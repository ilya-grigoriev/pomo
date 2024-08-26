CC=cc
CFLAGS=-g -lncurses

all:
	$(CC) $(CFLAGS) src/*.c -o pomo
