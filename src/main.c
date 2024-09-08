#include <ncurses.h>
#include <string.h>
#include "startpage.h"

WINDOW *create_newwin(int height, int width, int starty, int startx);


int main()
{	
	int row, col;

	initscr();			
	curs_set(0);
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
