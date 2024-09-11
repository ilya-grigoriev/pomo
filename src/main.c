#include <ncurses.h>
#include <string.h>
#include "startpage.h"
#include "print.h"

WINDOW *create_newwin(int height, int width, int starty, int startx);
int is_error_in_check_config_data(void);

int main()
{	
	int row, col;

	if (is_error_in_check_config_data()) {
		printf("invalid config.def.h\n");
		return -1;
	}

	initscr();			
	curs_set(0);
	noecho();
	getmaxyx(stdscr,row,col);

	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	
	initscr();
	cbreak();
	keypad(stdscr, TRUE);

	refresh();

	startpage(row, col);

	endwin();
	return 0;
}
