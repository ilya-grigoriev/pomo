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

char help_items[HELP_ITEMS][2][100] = {
	{"j", "\tmove down"},
	{"k", "\tmove up"},
	{"q", "\tquit from current window"},
	{"l", "\tenter to window"},
	{"h", "\tsame as `q`"},
	{"-", "\tdecrease size of something"},
	{"+", "\tincrease size of something"},
};

void help(int row, int col)
{
	int ch;

	print_help_logo(row, col);
	print_help_items(row, col);
	noecho();
	while ((ch = getch()) != 'q')
	{
		print_error("unavailable key `%c`", ch);
	}
}
