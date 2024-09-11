#include <stdio.h>
#include <ncurses.h>
#include "window.h"
#include "startpage.h"
#include "help.h"
#include "print.h"
#include "preset.h"
#include "settings.h"
#include "play.h"

int is_menu_active_window = 1;

int is_play_button(char ch);
int is_settings_button(char ch);
int is_help_button(char ch);

void startpage(int row, int col)
{
	int ch;

	print_logo(row, col);
	print_menu(row, col);
	WINDOW *menu_win = create_newwin(row, col, 0, 0);
	WINDOW *play_win, *settings_win, *help_win;

	while ((ch = getch()) != 'q') {
		if (ch == 'j' || ch == KEY_DOWN)
			cur_menu_active_item += (cur_menu_active_item+1 <= MENU_ITEMS) ? 1 : 0;
		else if (ch == 'k' || ch == KEY_UP)
			cur_menu_active_item -= (cur_menu_active_item-1 >= 1) ? 1 : 0;
		else if (is_play_button(ch)) {
			is_menu_active_window = 0;
			delwin(menu_win);

			play_win = create_newwin(row, col, 0, 0);
			play(row, col, play_win);
		}
		else if (is_settings_button(ch)) {
			is_menu_active_window = 0;
			delwin(menu_win);

			settings_win = create_newwin(row, col, 0, 0);
			settings(row, col, settings_win);
		}
		else if (is_help_button(ch)) {
			is_menu_active_window = 0;
			delwin(menu_win);

			help_win = create_newwin(row, col, 0, 0);
			help(row, col);
			delwin(help_win);
		}
		else
			print_error("unknown key `%c`", ch);

		if (is_menu_active_window)
			delwin(menu_win);
		else
			is_menu_active_window = 1;

		print_logo(row, col);
		print_menu(row, col);

		menu_win = create_newwin(row, col, 0, 0);
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
