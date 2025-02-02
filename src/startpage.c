#include <stdio.h>
#include <ncurses.h>
#include "window.h"
#include "startpage.h"
#include "help.h"
#include "print.h"
#include "preset.h"
#include "settings.h"
#include "play.h"

#define ROW getmaxy(stdscr)
#define COL getmaxx(stdscr)

int is_menu_active_window = 1;

int is_play_button(char ch);
int is_settings_button(char ch);
int is_help_button(char ch);

void refresh_menu_page(WINDOW **menu_win);

void startpage(void)
{
	WINDOW *menu_win = create_newwin(ROW, COL, 0, 0);
	refresh_menu_page(&menu_win);

	int ch;
	while ((ch = wgetch(stdscr)) != 'q') {
		if (ch == 'j' || ch == KEY_DOWN)
			cur_menu_active_item += (cur_menu_active_item+1 <= MENU_ITEMS) ? 1 : 0;
		else if (ch == 'k' || ch == KEY_UP)
			cur_menu_active_item -= (cur_menu_active_item-1 >= 1) ? 1 : 0;
		else if (ch == KEY_RESIZE)
			refresh();
		else if (ch == 'l') {
			is_menu_active_window = 0;
			delwin(menu_win);
		}
		else {
			if (ch != KEY_RESIZE)
				print_error("unknown key `%c`", ch);
		}

		if (is_play_button(ch))
			play(create_newwin(ROW, COL, 0, 0));
		else if (is_settings_button(ch))
			settings();
		else if (is_help_button(ch)) {
			help();
		}

		if (is_menu_active_window)
			delwin(menu_win);
		else
			is_menu_active_window = 1;

		refresh_menu_page(&menu_win);
	}
}

int is_play_button(char ch)
{
	return (ch == 'l' || ch == ENTER) && cur_menu_active_item == PLAY;
}

int is_settings_button(char ch)
{
	return (ch == 'l' || ch == ENTER) && cur_menu_active_item == SETTINGS;
}

int is_help_button(char ch)
{
	return (ch == 'l' || ch == ENTER) && cur_menu_active_item == HELP;
}

void refresh_menu_page(WINDOW **menu_win)
{
	*menu_win = create_newwin(ROW, COL, 0, 0);

	print_logo();
	print_menu();
	wrefresh(*menu_win);
}
