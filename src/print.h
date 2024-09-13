#include "play.h"

void print_logo(int row, int col);
void print_menu(int row, int col);
void print_settings_logo(int row, int col);
void print_settings_window(int row, int col);
void print_help_items(int row, int col);
void print_help_logo(int row, int col);
void print_pomodoros(int row, int col, int cur_pomodoros);
void print_clock(int row, int col, struct timer);
void print_error(char *error_message_template, ...);
