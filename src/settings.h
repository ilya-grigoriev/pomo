void settings(int row, int col, WINDOW *settings_win);

#define SETTINGS_ITEMS 5
extern char settings_str[SETTINGS_ITEMS][30];
extern int settings_int[SETTINGS_ITEMS];
extern int cur_settings_active_item;

#define SETTINGS_LOGO_ROW 5
extern char settings_logo[SETTINGS_LOGO_ROW][100];
#define SETTINGS_LOGO_MARGIN_OF_CENTER 10
