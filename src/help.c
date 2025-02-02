#include <ncurses.h>
#include "help.h"
#include "print.h"
#include "window.h"
#include "preset.h"
#include "print.h"

char help_logo[HELP_LOGO_ROW][30] = {
	R"( _   _ _____ _     ____  )",
	R"(| | | | ____| |   |  _ \ )",
	R"(| |_| |  _| | |   | |_)  )",
	R"(|  _  | |___| |___|  __/ )",
	R"(|_| |_|_____|_____|_|    )",
};

char help_items[HELP_ITEMS][2][MAX_LEN_HELP_ITEM] = {
	{"j", "    move down"},
	{"k", "    move up"},
	{"q", "    quit from current window"},
	{"-", "    decrease timer for one minute"},
	{"+", "    increase timer for one minute"},
	{"l", "    enter or increase value"},
	{"h", "    decrease value"},
	{"s", "    skip timer"},
	{"p", "    pause timer"},
};

void print_help_win(WINDOW **help_win);

void help()
{
	noecho();

	WINDOW *help_win;
	print_help_win(&help_win);

	int ch;
	while ((ch = getch()) != 'q')
		if (ch == KEY_RESIZE) {
			delwin(help_win);
			refresh();
			print_help_win(&help_win);
		}
		else
			print_error("unavailable key `%c`", ch);
}

void print_help_win(WINDOW **help_win) 
{
	print_help_logo();
	print_help_items();
	*help_win = create_newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 0);
}
