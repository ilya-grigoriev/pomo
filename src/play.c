#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "play.h"
#include "window.h"
#include "print.h"
#include "config.def.h"

static int glob_row, glob_col;
static WINDOW *glob_play_win;

static int is_threads_working = 1;

void play(int row, int col, WINDOW *play_win)
{
	int is_stop = 0;
	char ch;

	clock_t rest_work_time = WORK_TIME * 60; // secs

	print_work_clock(row, col, rest_work_time, is_stop);

	nodelay(play_win, 1);
	while (rest_work_time > 0 && is_threads_working) {
		napms(1000);

		ch = wgetch(play_win);
		if (ch == 'q')
			return;
		else if (ch == 's')
			break;
		else if (ch == 'p' || ch == ' ')
			is_stop = (is_stop == 0) ? 1 : 0;

		if (is_stop == 0)
			rest_work_time--;

		print_work_clock(row, col, rest_work_time, is_stop);
	}
}
