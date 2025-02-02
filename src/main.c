#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "startpage.h"
#include "print.h"
#include "config.def.h"
#include "args.h"

WINDOW *create_newwin(int height, int width, int starty, int startx);
int is_error_in_check_config_data(void);

int main(int argc, char *argv[])
{	
	if (is_error_in_check_config_data()) {
		printf("invalid config.def.h\n");
		return -1;
	}

	check_args(argc, argv);

	initscr();			
	curs_set(0);
	noecho();

	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	
	initscr();
	cbreak();
	keypad(stdscr, TRUE);

	refresh();

	startpage();

	endwin();
	return 0;
}
