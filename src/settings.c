#include <ncurses.h>
#include "print.h"
#include "preset.h"
#include "window.h"
#include "settings.h"

char settings_str[SETTINGS_ITEMS][30] = {
	"Long pause: <%d>",
	"Short pause: <%d>",
	"Pomodoros: <%d>",
	"Work time: <%d>",
	"RESET",
};
int settings_int[SETTINGS_ITEMS] = {
	LONG_PAUSE,
	SHORT_PAUSE,
	POMODOROS,
	WORK_TIME,
};
int cur_settings_active_item = 1;

char settings_logo[SETTINGS_LOGO_ROW][100] = {
	R"( ____  _____ _____ _____ ___ _   _  ____ ____  )",
	R"(/ ___|| ____|_   _|_   _|_ _| \ | |/ ___/ ___| )",
	R"(\___ \|  _|   | |   | |  | ||  \| | |  _\___ \ )",
	R"( ___) | |___  | |   | |  | || |\  | |_| |___) |)",
	R"(|____/|_____| |_|   |_| |___|_| \_|\____|____/ )",
};

void settings(int row, int col, WINDOW *settings_win)
{
	int ch;

	print_settings_logo(row, col);
	print_settings_window(row, col);
	while ((ch = getch()) != 'q')
	{
		if (ch == 'j')
			cur_settings_active_item += (cur_settings_active_item+1 <= SETTINGS_ITEMS) ? 1 : 0;
		else if (ch == 'k')
			cur_settings_active_item -= (cur_settings_active_item-1 >= 1) ? 1 : 0;
		else if (ch == 'l')
			if (cur_settings_active_item != SETTINGS_ITEMS)
				settings_int[cur_settings_active_item-1] += 1;
			else
				print_error("unavailable motion");
		else if (ch == 'h') 
			if (cur_settings_active_item != SETTINGS_ITEMS)
				settings_int[cur_settings_active_item-1] -= 1;
			else
				print_error("unavailable motion");
		else
			print_error("unknown key `%c`", ch);

		delwin(settings_win);
		print_settings_logo(row, col);
		print_settings_window(row, col);
		settings_win = create_newwin(row, col, 0, 0);
	}
}
