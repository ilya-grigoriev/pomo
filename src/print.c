#include <ncurses.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "preset.h"
#include "settings.h"

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

void print_settings_window(int row, int col)
{
	char *cur_line = malloc(sizeof(char *));
	int center_row, center_col;

	for (int i = 0; i < SETTINGS_ITEMS; i++) {
		sprintf(cur_line, settings_str[i], settings_int[i]);
		center_row = row/2 + i;
		center_col = (col-strlen(cur_line)) / 2;

		if (i+1 == cur_settings_active_item) {
			attron(A_BOLD);
			mvprintw(center_row, center_col - ARROW_COL, "%s", cur_line);
			attroff(A_BOLD);
		}
		else {
			attron(A_DIM);
			mvprintw(center_row, center_col, "%s", cur_line);
			attroff(A_DIM);
		}
	}

	free(cur_line);
}

void print_error(char *error_message_template, ...)
{
	va_list args;
	va_start(args, error_message_template);

	char *error_message = malloc(sizeof(char *));
	vsprintf(error_message, error_message_template, args);
	mvprintw(LINES - 2, 2, "%s", error_message);
	free(error_message);

	va_end(args);
}
