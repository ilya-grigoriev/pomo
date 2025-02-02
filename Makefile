CC=cc
CFLAGS=-g -Wall -lncurses

all:
	@mkdir -p bin/
	$(CC) $(CFLAGS) src/*.c -o bin/pomo

install:
	@mkdir -p /usr/bin/
	$(CC) $(CFLAGS) src/*.c -o bin/pomo
	cp bin/pomo /usr/bin
