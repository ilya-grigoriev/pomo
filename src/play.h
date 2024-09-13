#include <ncurses.h>
#include <time.h>

void run_clock(int row, int col, WINDOW *play_win);
void get_signal(void);
void play(int row, int col, WINDOW *play_win);

#ifndef PLAY_H
#define PLAY_H
struct Play {
	int is_stop;
	int pomodoros;
	clock_t rest_time;
};
#endif
