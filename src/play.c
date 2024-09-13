#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "window.h"
#include "print.h"
#include "config.def.h"
#include "play.h"
#include "settings.h"

int run_work_timer(int row, int col, WINDOW *play_win);
int run_chill_timer(int row, int col, WINDOW *play_win);

struct Play Play_T;

void play(int row, int col, WINDOW *play_win)
{
	Play_T.is_stop = 0;

	nodelay(play_win, 1);
	run_work_timer(row, col, play_win);
	run_chill_timer(row, col, play_win);
}

int run_work_timer(int row, int col, WINDOW *play_win)
{
	Play_T.rest_time = settings_vals[0] * 60; // secs
	int ch;

	print_clock(row, col, Play_T);
	while (Play_T.rest_time > 0) {
		napms(1000);

		ch = wgetch(play_win);
		if (ch == 'q')
			return 0;
		else if (ch == 's')
			break;
		else if (ch == 'p' || ch == ' ')
			Play_T.is_stop = (Play_T.is_stop == 0) ? 1 : 0;

		if (Play_T.is_stop == 0)
			Play_T.rest_time--;

		print_clock(row, col, Play_T);
	}
}

int run_chill_timer(int row, int col, WINDOW *play_win)
{
	Play_T.rest_time = SHORT_PAUSE * 60; // secs
	int ch;

	print_clock(row, col, Play_T);
	while (Play_T.rest_time > 0) {
		napms(1000);

		ch = wgetch(play_win);
		if (ch == 'q')
			return 0;
		else if (ch == 's')
			break;
		else if (ch == 'p' || ch == ' ')
			Play_T.is_stop = (Play_T.is_stop == 0) ? 1 : 0;

		if (Play_T.is_stop == 0)
			Play_T.rest_time--;

		print_clock(row, col, Play_T);
	}
}
