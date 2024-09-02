CC=cc
CFLAGS=-g -lncurses

all:
	@mkdir -p bin/
	$(CC) $(CFLAGS) src/*.c -o bin/pomo
