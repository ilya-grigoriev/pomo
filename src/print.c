#include <ncurses.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "preset.h"
#include "settings.h"
#include "config.def.h"
#include "help.h"
#include "print.h"

void print_logo(int row, int col)
{
	char *cur_line;
	int center_row, center_col;

	for (int i = 0; i < LOGO_ROW; i++) {
		cur_line = logo[i];
		center_row = row/2 - LOGO_MARGIN_OF_CENTER + i;
		center_col = (col-strlen(cur_line)) / 2;

		mvprintw(center_row, center_col, "%s", cur_line);
	}
}

void print_menu(int row, int col)
{
	char *cur_line;
	int center_row, center_col;

	for (int i = 0; i < MENU_ITEMS; i++) {
		cur_line = menu[i];
		center_row = row/2 + i;
		center_col = (col-strlen(cur_line)) / 2;

		if (i+1 == cur_menu_active_item) {
			attron(A_BOLD);
			mvprintw(center_row, center_col - ARROW_COL, "-> %s <-", cur_line);
			attroff(A_BOLD);
		}
		else {
			attron(A_DIM);
			mvprintw(center_row, center_col, "%s", cur_line);
			attroff(A_DIM);
		}
	}
}

int is_active_button(int n)
{
	return n == cur_settings_active_item;
}

void print_settings_window(int row, int col)
{
	char *cur_line = malloc(sizeof(char *));
	int center_row, center_col;

	for (int i = 0; i < SETTINGS_ITEMS; i++) {
		center_row = row/2 + i;
		center_col = col * 0.4575;

		if (i+1 != SETTINGS_ITEMS)
			sprintf(cur_line, settings_str[i], settings_vals[i]);
		else {
			mvprintw(center_row, center_col, "");
			center_row++;
			sprintf(cur_line, settings_str[i]);
			center_col = (col - strlen(cur_line)) / 2;
		}

		if (is_active_button(i+1)) {
			attron(A_BOLD);
			mvprintw(center_row, center_col, "%s", cur_line);
			attroff(A_BOLD);
		}
		else {
			attron(A_DIM);
			mvprintw(center_row, center_col, "%s", cur_line);
			attroff(A_DIM);
		}
	}
}

void print_settings_logo(int row, int col)
{
	char *cur_line = malloc(sizeof(char *));
	int center_row, center_col;

	for (int i = 0; i < SETTINGS_LOGO_ROW; i++) {
		cur_line = settings_logo[i];
		center_row = row/2 - SETTINGS_LOGO_MARGIN_OF_CENTER + i;
		center_col = (col-strlen(cur_line)) / 2;

		mvprintw(center_row, center_col, "%s", cur_line);
	}
}

void print_help_logo(int row, int col)
{
	char *cur_line = malloc(sizeof(char *));
	int center_row, center_col;

	for (int i = 0; i < HELP_LOGO_ROW; i++) {
		cur_line = help_logo[i];
		center_row = row/2 - HELP_LOGO_MARGIN_OF_CENTER + i;
		center_col = (col-strlen(cur_line)) / 2;

		mvprintw(center_row, center_col, "%s", cur_line);
	}
}

void print_help_items(int row, int col)
{
	char *cur_hotkey = malloc(sizeof(char *));
	char *cur_help_message = malloc(sizeof(char *));
	int center_row, center_col;

	for (int i = 0; i < HELP_ITEMS; i++)
	{
		center_row = row/2 + i;
		center_col = col * 0.425;

		cur_hotkey = help_items[i][0];
		cur_help_message = help_items[i][1];
		
		attron(A_BOLD);
		mvprintw(center_row, center_col, "%s", cur_hotkey);
		attroff(A_BOLD);

		mvprintw(center_row, center_col+1, "%s", cur_help_message);
	}
}

#define LEFT_UPPER_CORNER_X 1
#define LEFT_UPPER_CORNER_Y 2
void print_pomodoros(int row, int col, int cur_pomodoros)
{
	attron(A_BOLD);
	attron(COLOR_PAIR(2));
	mvprintw(LEFT_UPPER_CORNER_X, LEFT_UPPER_CORNER_Y, "%d", cur_pomodoros);
	attroff(COLOR_PAIR(2));
	attroff(A_BOLD);
}

void print_clock(int row, int col, struct timer Timer)
{
	int mins, rest_secs;
	char *message;

	if (Timer.type_timer == TYPE_TIMER_WORK)
		message = "Current time";
	else if (Timer.type_timer == TYPE_TIMER_CHILL)
		message = " Chill time ";
	else if (Timer.type_timer == TYPE_TIMER_LONG_CHILL)
		message = "Long chill time";

	mins = Timer.rest_time / 60;
	rest_secs = Timer.rest_time - (mins * 60);

	attron(A_BOLD);
	mvprintw(row/2, (col-strlen(message)) / 2, "%s", message);
	attroff(A_BOLD);

	if (Timer.is_stop == 0) {
		attron(A_BOLD);
		mvprintw(row/2+1, (col-5) / 2, "%02d:%02d", mins, rest_secs);
		attroff(A_BOLD);
	}
	else {
		attron(A_DIM);
		mvprintw(row/2+1, (col-5) / 2, "%02d:%02d", mins, rest_secs);
		attroff(A_DIM);
	}

	refresh();
}

void print_error(char *error_message_template, ...)
{
	va_list args;
	va_start(args, error_message_template);

	char *error_message = malloc(sizeof(char *));
	vsprintf(error_message, error_message_template, args);

	attron(COLOR_PAIR(1));
	mvprintw(LINES - 2, 2, "%s", error_message);
	attroff(COLOR_PAIR(1));

	free(error_message);

	va_end(args);
}
