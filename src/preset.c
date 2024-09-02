#include "preset.h"

char logo[LOGO_ROW][30] = {
	R"( ____   ___  __  __  ___  )",
	R"(|  _ \ / _ \|  \/  |/ _ \ )",
	R"(| |_) | | | | |\/| | | | |)",
	R"(|  __/| |_| | |  | | |_| |)",
	R"(|_|    \___/|_|  |_|\___/ )"
};
char menu[MENU_ITEMS][30] = {
	"Play",
	"Settings",
	"Help",
};
int cur_menu_active_item = 1;
