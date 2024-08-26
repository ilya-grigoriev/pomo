#include <ncurses.h>
#include <string.h>
#include "preset.h"
#include "print.h"
#include "settings.h"
#include "window.h"

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int is_menu_active_window = 1;

int main()
{	
	int ch;
	int row, col;
	extern int cur_menu_active_item;

	initscr();			
	curs_set(0);
	getmaxyx(stdscr,row,col);
	
	initscr();
	cbreak();
	keypad(stdscr, TRUE);

	int height = row;
	int width = col;

	refresh();

	print_logo(row, col);
	print_menu(row, col);
	WINDOW *menu_win = create_newwin(height, width, 0, 0);
	WINDOW *settings_win, *help_win;

	while ((ch = getch()) != 'q') {
		if (ch == 'j')
			cur_menu_active_item += (cur_menu_active_item+1 <= MENU_ITEMS) ? 1 : 0;
		else if (ch == 'k')
			cur_menu_active_item -= (cur_menu_active_item-1 >= 1) ? 1 : 0;
		else if (ch == 'l' && cur_menu_active_item == SETTINGS) {
			is_menu_active_window = 0;
			delwin(menu_win);
			settings_win = create_newwin(height, width, 0, 0);
			settings(row, col, settings_win);
			delwin(settings_win);
		}
		else
			print_error("unknown key `%c`", ch);

		if (is_menu_active_window)
			delwin(menu_win);
		else
			is_menu_active_window = 1;
		print_logo(row, col);
		print_menu(row, col);
		menu_win = create_newwin(height, width, 0, 0);
	}

	endwin();
	return 0;
}
