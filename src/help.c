#include <ncurses.h>
#include "help.h"
#include "print.h"
#include "preset.h"
#include "print.h"

char help_logo[HELP_LOGO_ROW][30] = {
	R"( _   _ _____ _     ____  )",
	R"(| | | | ____| |   |  _ \ )",
	R"(| |_| |  _| | |   | |_)  )",
	R"(|  _  | |___| |___|  __/ )",
	R"(|_| |_|_____|_____|_|    )",
};

char help_items[HELP_ITEMS][100] = {
	"`j` -- move down",
	"`k` -- move up",
	"`q` -- quit from current window",
	"`l` -- enter to window or increase size of something",
	"`h` -- decrease size of something",
};

void help(int row, int col)
{
	int ch;

	print_help_logo(row, col);
	print_help_items(row, col);
	while ((ch = getch()) != 'q' && (ch != 'h'))
	{
		print_error("unknown key `%c`", ch);
	}
}
