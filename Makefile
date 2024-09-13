CC=cc
CFLAGS=-g -Wall -lncurses

all:
	@mkdir -p bin/
	$(CC) $(CFLAGS) src/*.c -o bin/pomo
