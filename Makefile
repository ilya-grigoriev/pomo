.PHONY: all clean install

VERSION = 1.0

CC=cc
CFLAGS=-g -Wall -lncurses

PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

all:
	@mkdir -p bin/
	$(CC) $(CFLAGS) src/*.c -o bin/pomo

clean:
	rm -rf bin/

install: all
	@mkdir -p /usr/bin/
	$(CC) $(CFLAGS) src/*.c -o bin/pomo
	cp bin/pomo /usr/bin
	mkdir -p $(MANPREFIX)/man1
	sed "s/VERSION/$(VERSION)/g" < pomo.1 > $(MANPREFIX)/man1/pomo.1
	chmod 644 $(MANPREFIX)/man1/pomo.1

uninstall:
	rm -rf /usr/bin/pomo
	rm -rf $(MANPREFIX)/man1/pomo.1
