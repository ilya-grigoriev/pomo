#include <ncurses.h>
#include "print.h"
#include "preset.h"
#include "window.h"
#include "settings.h"
#include "config.def.h"

char settings_str[SETTINGS_ITEMS][30] = {
	"Long pause: <%d>",
	"Short pause: <%d>",
	"Pomodoros: <%d>",
	"Work time: <%d>",
	"RESET",
};
int settings_vals[SETTINGS_ITEMS] = {
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
		if (ch == 'j' || ch == KEY_DOWN)
			cur_settings_active_item += (cur_settings_active_item+1 <= SETTINGS_ITEMS) ? 1 : 0;
		else if (ch == 'k' || ch == KEY_UP)
			cur_settings_active_item -= (cur_settings_active_item-1 >= 1) ? 1 : 0;
		else if ((ch == 'l' || ch == ENTER) && cur_settings_active_item == SETTINGS_ITEMS)
				reset_settings();
		else if (ch == 'l' || ch == KEY_RIGHT)
			if (cur_settings_active_item != SETTINGS_ITEMS) // no reset button
				settings_vals[cur_settings_active_item-1] += 1;
		else if (ch == 'h' || ch == KEY_LEFT) 
			if (cur_settings_active_item != SETTINGS_ITEMS)
				if (settings_vals[cur_settings_active_item-1] - 1 > 0)
					settings_vals[cur_settings_active_item-1] -= 1;
				else
					print_error("min value is 1\n");
			else
				print_error("unavailable motion");
		else
			print_error("unknown key `%c`", ch);

		delwin(settings_win);
		print_settings_logo(row, col);
		print_settings_window(row, col);
		settings_win = create_newwin(row, col, 0, 0);
	}

	cur_settings_active_item = 1;
}

void reset_settings(void)
{
	int default_settings_vals[SETTINGS_ITEMS] = {
		LONG_PAUSE,
		SHORT_PAUSE,
		POMODOROS,
		WORK_TIME,
	};

	for (int i = 0; i < SETTINGS_ITEMS; i++) {
		settings_vals[i] = default_settings_vals[i];
	}
}
