#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "window.h"
#include "print.h"
#include "config.def.h"
#include "play.h"
#include "settings.h"
#include "args.h"

#define QUIT 1
#define MINUTE 60

struct timer Timer;

void play(WINDOW *play_win)
{
	int state;
	int pomodoros = settings_vals[POMODOROS_INDEX];
	Timer.is_stop = 0;

	nodelay(play_win, 1);

	int cur_pomodoros = 0;
	for (int count_launches_timer = 1; count_launches_timer <= pomodoros * 2; count_launches_timer++) {
		if (count_launches_timer % 2 != 0) {
			Timer.type_timer = TYPE_TIMER_WORK;
			cur_pomodoros++;
		}
		else if (count_launches_timer == pomodoros * 2 || count_launches_timer % 8 == 0) 
				Timer.type_timer = TYPE_TIMER_LONG_CHILL;
		else
			Timer.type_timer = TYPE_TIMER_CHILL;

		state = run_timer(play_win, cur_pomodoros);
		if (state == QUIT)
			break;
	}
}

void print_play_win(int pomodoros);

#define TRIGGER 1.0
int run_timer(WINDOW *play_win, int pomodoros)
{
	Timer.rest_time = settings_vals[Timer.type_timer] * MINUTE;

	print_play_win(pomodoros);

	char ch;
	time_t before = time(NULL);
	while (Timer.rest_time > 0) {
		if (difftime(time(NULL), before) >= TRIGGER) {
			if (Timer.is_stop == 0)
				Timer.rest_time--;
			before = time(NULL);
		}
		print_play_win(pomodoros);

		ch = wgetch(play_win);
		if (ch == 'q')
			return QUIT;
		else if (ch == KEY_RESIZE)
			refresh();
		else if (ch == 's')
			break;
		else if (ch == 'p' || ch == ' ')
			Timer.is_stop = (Timer.is_stop == 0) ? 1 : 0;
		else if (ch == '+')
			Timer.rest_time += MINUTE;
		else if (ch == '-')
			Timer.rest_time -= (Timer.rest_time - MINUTE > 0) ? MINUTE : 0;

		napms(1000/60);
	}

	if (NOTIFICATION) {
		system("herbe \"timed out\"");
	}
}

void print_play_win(int pomodoros) {
	erase();
	print_pomodoros(pomodoros);
	print_clock(Timer);
}
