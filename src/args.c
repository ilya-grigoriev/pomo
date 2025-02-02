#include <string.h>
#include <stdlib.h>
#include "args.h"

int NOTIFICATION = 0;

void check_args(int argc, char *argv[])
{
	if (argc == 2) {
		if (strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "--notification") == 0)
			NOTIFICATION = 1;
	}
}
