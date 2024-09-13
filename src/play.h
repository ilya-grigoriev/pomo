#include <ncurses.h>
#include <time.h>

void run_clock(int row, int col, WINDOW *play_win);
void get_signal(void);
void play(int row, int col, WINDOW *play_win);
int run_timer(int, int, WINDOW*, int pomodoros);

#define TYPE_TIMER_WORK 0
#define TYPE_TIMER_CHILL 1
#define TYPE_TIMER_LONG_CHILL 2

#ifndef PLAY_H
#define PLAY_H
struct timer {
	int is_stop;
	int pomodoros;
	int type_timer; // `WORK`, `CHILL`, `LONG_CHILL`
	clock_t rest_time;
};
#endif
