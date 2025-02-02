#include <ncurses.h>

void settings();

#define POMODOROS_INDEX 3

#define SETTINGS_ITEMS 5
#define MAX_LEN_SETTING_ITEM 20
extern char settings_str[SETTINGS_ITEMS][MAX_LEN_SETTING_ITEM];
extern int settings_vals[SETTINGS_ITEMS];
extern int cur_settings_active_item;

#define SETTINGS_LOGO_ROW 5
extern char settings_logo[SETTINGS_LOGO_ROW][100];
#define SETTINGS_LOGO_MARGIN_OF_CENTER 10

void reset_settings(void);
