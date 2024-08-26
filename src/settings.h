void settings(int row, int col, WINDOW *settings_win);

#define SETTINGS_ITEMS 4
extern char settings_str[SETTINGS_ITEMS][30];
extern int settings_int[SETTINGS_ITEMS];
extern int cur_settings_active_item;

#define LONG_PAUSE 30
#define SHORT_PAUSE 5
#define POMODOROS 4
#define WORK_TIME 30
