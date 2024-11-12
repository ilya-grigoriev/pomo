#include "config.def.h"

int is_error_in_check_config_data(void)
{
	return (LONG_PAUSE < 1) || (SHORT_PAUSE < 1) || (POMODOROS < 1) || (WORK_TIME < 1);
}
